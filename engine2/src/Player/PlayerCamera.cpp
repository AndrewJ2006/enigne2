#include "PlayerCamera.h"
#include "Backend.h"
#include "PhysicsManager.h"
#include "RaycastingPx.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include <PxPhysicsAPI.h>
#include <stdexcept>

using namespace physx;

PlayerCamera::PlayerCamera()
    : Camera(glm::vec3(0.0f, 1.75f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        0.0f),
    m_raycast(PhysicsManager::Get().GetScene()),
    m_jumpPressedLastFrame(false)
{
}

bool PlayerCamera::InitPhysics() {
    if (!m_physics.Init(PxVec3(0.0f, 1.75f, 0.0f))) {
        throw std::runtime_error("Failed to initialize PlayerPhysics");
    }
    return true;
}

void PlayerCamera::Update(float deltaX, float deltaY, float deltaTime) {
    // Update camera rotation with mouse input
    Yaw += deltaX * m_mouseSensitivity;
    Pitch += deltaY * m_mouseSensitivity;
    Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
    updateCameraVectors();

    PxController* controller = m_physics.GetController();
    if (!controller) {
        throw std::runtime_error("PlayerPhysics controller is null");
    }

    PxVec3 movement(0.0f);

    if (Backend::IsKeyPressed(GLFW_KEY_W))
        movement += PxVec3(Front.x, 0.0f, Front.z);
    if (Backend::IsKeyPressed(GLFW_KEY_S))
        movement -= PxVec3(Front.x, 0.0f, Front.z);
    if (Backend::IsKeyPressed(GLFW_KEY_A))
        movement -= PxVec3(Right.x, 0.0f, Right.z);
    if (Backend::IsKeyPressed(GLFW_KEY_D))
        movement += PxVec3(Right.x, 0.0f, Right.z);

    if (movement.magnitudeSquared() > 0.01f)
        movement = movement.getNormalized();

    m_physics.Move(movement);

    // Jump input detection and ground check
    bool jumpPressed = Backend::IsKeyPressed(GLFW_KEY_SPACE);
    bool onGround = m_physics.IsOnGround();

    if (jumpPressed && !m_jumpPressedLastFrame && onGround) {
        m_physics.Jump();
    }
    m_jumpPressedLastFrame = jumpPressed;

    m_physics.Update(deltaTime);

    // Sync camera position with physics controller, convert PxExtendedVec3 to PxVec3
    PxExtendedVec3 extendedPos = controller->getPosition();
    Position = glm::vec3(
        static_cast<float>(extendedPos.x),
        static_cast<float>(extendedPos.y),
        static_cast<float>(extendedPos.z));
}

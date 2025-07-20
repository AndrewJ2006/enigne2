#include "PlayerCamera.h"
#include "Backend.h"
#include "ManagerPx.h"
#include "Door.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <PxPhysicsAPI.h>
#include <stdexcept>

using namespace physx;

extern std::vector<Door*> g_Doors;

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

void PlayerCamera::Update(float deltaTime) {
    // Update camera rotation based on mouse movement
    float deltaX, deltaY;
    Backend::GetMouseDelta(deltaX, deltaY);
    Yaw += deltaX * m_mouseSensitivity;
    Pitch += deltaY * m_mouseSensitivity;
    Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
    updateCameraVectors();

    PxController* controller = m_physics.GetController();
    if (!controller) throw std::runtime_error("PlayerPhysics controller is null");

    // Handle player movement input
    PxVec3 movement(0.0f);
    if (Backend::IsKeyPressed(GLFW_KEY_W)) movement += PxVec3(Front.x, 0.0f, Front.z);
    if (Backend::IsKeyPressed(GLFW_KEY_S)) movement -= PxVec3(Front.x, 0.0f, Front.z);
    if (Backend::IsKeyPressed(GLFW_KEY_A)) movement -= PxVec3(Right.x, 0.0f, Right.z);
    if (Backend::IsKeyPressed(GLFW_KEY_D)) movement += PxVec3(Right.x, 0.0f, Right.z);

    if (movement.magnitudeSquared() > 0.01f)
        movement = movement.getNormalized();

    PxVec3 moveWithSpeed = movement * m_moveSpeed * deltaTime;
    m_physics.Move(moveWithSpeed);

    // Jump input handling
    bool jumpPressed = Backend::IsKeyPressed(GLFW_KEY_SPACE);
    if (jumpPressed && !m_jumpPressedLastFrame && m_physics.IsOnGround()) {
        m_physics.Jump();
    }
    m_jumpPressedLastFrame = jumpPressed;

    // Door interaction on 'F' key press (with debounce)
    static bool fPressedLastFrame = false;
    bool fPressed = Backend::IsKeyPressed(GLFW_KEY_F);

    if (fPressed && !fPressedLastFrame) {
        PxScene* scene = PhysicsManager::Get().GetScene();
        RaycastingPx raycaster(scene);

        PxVec3 origin(Position.x, Position.y + 1.75f, Position.z);
        glm::vec3 frontNorm = glm::normalize(Front);
        PxVec3 direction(frontNorm.x, frontNorm.y, frontNorm.z);

        PxRaycastBuffer hitBuffer;
        float maxDistance = 3.5f;

        if (raycaster.Raycast(origin, direction, maxDistance, hitBuffer)) {
            PxActor* hitActor = hitBuffer.block.actor;
            for (Door* door : g_Doors) {
                if (door->GetRigidActor() == hitActor) {
                    door->ToggleOpenClose();
                    break;
                }
            }
        }
    }
    fPressedLastFrame = fPressed;

    // Update physics simulation for player
    m_physics.Update(deltaTime);

    // Update camera position from physics controller position
    PxExtendedVec3 extendedPos = controller->getPosition();
    Position = glm::vec3(static_cast<float>(extendedPos.x),
        static_cast<float>(extendedPos.y),
        static_cast<float>(extendedPos.z));
}

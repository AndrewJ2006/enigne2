#include "Player.h"
#include "Backend.h"
#include "Physics.h"
#include "Door.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <PxPhysicsAPI.h>
#include <stdexcept>

using namespace physx;

extern std::vector<Door*> g_Doors;
bool Player::fPressedLastFrame = false;

Player::Player()
    : m_raycast(PhysicsManager::Get().GetScene()),
      m_jumpPressedLastFrame(false)
{
}

bool Player::InitPhysics() {
    if (!m_physics.Init(PxVec3(0.0f, 1.75f, 0.0f))) {
        throw std::runtime_error("Failed to initialize PlayerPhysics");
    }
    return true;
}

void Player::Update(float deltaTime) {
    // Update camera rotation based on mouse movement
    float deltaX, deltaY;
    Backend::GetMouseDelta(deltaX, deltaY);

    m_camera.SetYaw(m_camera.GetYaw() + deltaX * m_camera.GetMouseSensitivity());

    float newPitch = glm::clamp(m_camera.GetPitch() + deltaY * m_camera.GetMouseSensitivity(), -89.0f, 89.0f);
    m_camera.SetPitch(newPitch);

    // Call public wrapper to update camera vectors
    m_camera.UpdateCameraVectors();

    PxController* controller = m_physics.GetController();
    if (!controller) throw std::runtime_error("PlayerPhysics controller is null");

    // Handle player movement input
    PxVec3 movement(0.0f);
    if (Backend::IsKeyPressed(GLFW_KEY_W)) movement += PxVec3(m_camera.GetFront().x, 0.0f, m_camera.GetFront().z);
    if (Backend::IsKeyPressed(GLFW_KEY_S)) movement -= PxVec3(m_camera.GetFront().x, 0.0f, m_camera.GetFront().z);
    if (Backend::IsKeyPressed(GLFW_KEY_A)) movement -= PxVec3(m_camera.GetRight().x, 0.0f, m_camera.GetRight().z);
    if (Backend::IsKeyPressed(GLFW_KEY_D)) movement += PxVec3(m_camera.GetRight().x, 0.0f, m_camera.GetRight().z);

    if (movement.magnitudeSquared() > 0.01f)
        movement = movement.getNormalized();

    PxVec3 moveWithSpeed = movement * m_camera.GetMovementSpeed() * deltaTime;
    m_physics.Move(moveWithSpeed);

    // Jump input handling
    bool jumpPressed = Backend::IsKeyPressed(GLFW_KEY_SPACE);
    if (jumpPressed && !m_jumpPressedLastFrame && m_physics.IsOnGround()) {
        m_physics.Jump();
    }
    m_jumpPressedLastFrame = jumpPressed;

    // Door interaction on 'F' key press (with debounce)
    bool fPressed = Backend::IsKeyPressed(GLFW_KEY_F);

    if (fPressed && !fPressedLastFrame) {
        PxScene* scene = PhysicsManager::Get().GetScene();
        RaycastingPx raycaster(scene);

        glm::vec3 camPos = m_camera.GetPosition();
        PxVec3 origin(camPos.x, camPos.y + 1.75f, camPos.z);
        glm::vec3 frontNorm = glm::normalize(m_camera.GetFront());
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

    // Sync camera position to physics controller position
    PxExtendedVec3 extendedPos = controller->getPosition();
    m_camera.SetPosition(glm::vec3(static_cast<float>(extendedPos.x),
        static_cast<float>(extendedPos.y),
        static_cast<float>(extendedPos.z)));
}

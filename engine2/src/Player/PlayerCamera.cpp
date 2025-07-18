#include "PlayerCamera.h"
#include "Backend.h"
#include "Door.h"
#include "ManagerPx.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <PxPhysicsAPI.h>
#include <stdexcept>
#include <vector>

using namespace physx;

extern std::vector<Door*> g_Doors;

PlayerCamera::PlayerCamera()
    : Camera(glm::vec3(0.0f, 1.75f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        0.0f),
    m_jumpPressedLastFrame(false),
    m_mouseSensitivity(0.1f),
    m_collisionsEnabled(true) {
    m_scene = PhysicsManager::Get().GetScene();
}

PlayerCamera::~PlayerCamera() = default;

bool PlayerCamera::InitPhysics() {
    if (!m_player.Init(PxVec3(0.0f, 1.75f, 0.0f))) {
        throw std::runtime_error("Failed to initialize PlayerPhysics");
    }
    m_player.SetSpeed(5.0f);
    return true;
}

void PlayerCamera::DisableCollisions() {
    PxController* controller = m_player.GetController();
    if (!controller) return;

    PxRigidActor* actor = controller->getActor();
    if (!actor) return;

    PxU32 nbShapes = actor->getNbShapes();
    if (nbShapes == 0) return;

    std::vector<PxShape*> shapes(nbShapes);
    actor->getShapes(shapes.data(), nbShapes);

    for (PxShape* shape : shapes) {
        shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
        shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, false);
    }
}

void PlayerCamera::EnableCollisions() {
    PxController* controller = m_player.GetController();
    if (!controller) return;

    PxRigidActor* actor = controller->getActor();
    if (!actor) return;

    PxU32 nbShapes = actor->getNbShapes();
    if (nbShapes == 0) return;

    std::vector<PxShape*> shapes(nbShapes);
    actor->getShapes(shapes.data(), nbShapes);

    for (PxShape* shape : shapes) {
        shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
        shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
    }
}

void PlayerCamera::Update(float deltaX, float deltaY, float deltaTime,
    const glm::vec3& rayOriginOverride,
    const glm::vec3& rayDirectionOverride) {
    // Update camera orientation from mouse movement
    Yaw += deltaX * m_mouseSensitivity;
    Pitch += deltaY * m_mouseSensitivity;
    Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
    updateCameraVectors();

    PxController* controller = m_player.GetController();
    if (!controller) {
        throw std::runtime_error("Player controller is null");
    }

    // Process keyboard movement
    PxVec3 movement(0.0f);
    if (Backend::IsKeyPressed(GLFW_KEY_W)) movement += PxVec3(Front.x, 0.0f, Front.z);
    if (Backend::IsKeyPressed(GLFW_KEY_S)) movement -= PxVec3(Front.x, 0.0f, Front.z);
    if (Backend::IsKeyPressed(GLFW_KEY_A)) movement -= PxVec3(Right.x, 0.0f, Right.z);
    if (Backend::IsKeyPressed(GLFW_KEY_D)) movement += PxVec3(Right.x, 0.0f, Right.z);

    if (movement.magnitudeSquared() > 0.01f)
        movement = movement.getNormalized();

    m_player.Move(movement);

    // Handle jump input
    bool jumpPressed = Backend::IsKeyPressed(GLFW_KEY_SPACE);
    if (jumpPressed && !m_jumpPressedLastFrame && m_player.IsOnGround()) {
        m_player.Jump();
    }
    m_jumpPressedLastFrame = jumpPressed;

    // Handle interaction and toggle collisions on F press
    static bool fPressedLastFrame = false;
    bool fPressed = Backend::IsKeyPressed(GLFW_KEY_F);

    if (fPressed && !fPressedLastFrame) {
        // Toggle collisions ON/OFF
        if (m_collisionsEnabled) {
            DisableCollisions();
            m_collisionsEnabled = false;
        }
        else {
            EnableCollisions();
            m_collisionsEnabled = true;
        }

        // Raycast for door interaction
        glm::vec3 rayOriginVec = (rayOriginOverride != glm::vec3(-1.0f))
            ? rayOriginOverride
            : glm::vec3(Position.x, Position.y + 1.5f, Position.z); // raise origin approx head height

        glm::vec3 rayDirVec = (rayDirectionOverride != glm::vec3(-1.0f))
            ? rayDirectionOverride
            : glm::normalize(Front);

        const float originOffsetDistance = 0.3f; // offset forward so ray doesn't hit self
        glm::vec3 adjustedOrigin = rayOriginVec + rayDirVec * originOffsetDistance;

        PxVec3 origin(adjustedOrigin.x, adjustedOrigin.y, adjustedOrigin.z);
        PxVec3 direction(rayDirVec.x, rayDirVec.y, rayDirVec.z);

        PxRaycastBuffer hitBuffer(nullptr, 0); // Fix for PhysX ctor error

        PxQueryFilterData filterData;
        filterData.flags = PxQueryFlag::eSTATIC | PxQueryFlag::eDYNAMIC;

        bool hit = false;
        if (m_scene) {
            hit = m_scene->raycast(
                origin,
                direction,
                3.5f, // max distance
                hitBuffer,
                PxHitFlag::eDEFAULT,
                filterData);
        }

        if (hit && hitBuffer.hasBlock) {
            PxActor* hitActor = hitBuffer.block.actor;
            if (hitActor) {
                for (Door* door : g_Doors) {
                    if (door && door->GetRigidActor() == hitActor) {
                        door->ToggleOpenClose();
                        break;
                    }
                }
            }
        }
    }
    fPressedLastFrame = fPressed;

    // Sync camera with controller position
    m_player.Update(deltaTime);

    PxExtendedVec3 extendedPos = controller->getPosition();
    Position = glm::vec3(static_cast<float>(extendedPos.x),
        static_cast<float>(extendedPos.y),
        static_cast<float>(extendedPos.z));
}

void PlayerCamera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

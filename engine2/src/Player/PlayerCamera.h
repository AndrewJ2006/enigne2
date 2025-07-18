#pragma once

#include "Camera.h"
#include "PlayerPx.h"
#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

class PlayerCamera : public Camera {
public:
    PlayerCamera();
    ~PlayerCamera();

    bool InitPhysics();

    void Update(float deltaX, float deltaY, float deltaTime,
        const glm::vec3& rayOriginOverride = glm::vec3(-1.0f),
        const glm::vec3& rayDirectionOverride = glm::vec3(-1.0f));

    void DisableCollisions();
    void EnableCollisions();

private:
    void updateCameraVectors();

    PlayerPhysics m_player;
    physx::PxScene* m_scene = nullptr;
    physx::PxRaycastBuffer m_raycast;

    bool m_jumpPressedLastFrame;
    bool m_collisionsEnabled;
    float m_mouseSensitivity;
};

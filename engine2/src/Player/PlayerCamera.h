#pragma once

#include "Camera.h"
#include "Physics.h"

// Forward declaration
class Door;

class PlayerCamera : public Camera {
public:
    PlayerCamera();

    bool InitPhysics();
    void Update(float deltaTime) override;

private:
    float m_mouseSensitivity = 0.1f;
    float m_moveSpeed = 90.0f;

    PlayerPhysics m_physics;
    RaycastingPx m_raycast;

    bool m_jumpPressedLastFrame = false;
};

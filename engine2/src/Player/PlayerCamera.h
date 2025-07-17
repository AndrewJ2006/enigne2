#pragma once

#include "Camera.h"
#include "PlayerPx.h"
#include "RaycastingPx.h"

// Forward declaration to avoid include cycle
class Door;

class PlayerCamera : public Camera {
public:
    PlayerCamera();

    bool InitPhysics();
    void Update(float deltaX, float deltaY, float deltaTime);

private:
    float m_mouseSensitivity = 0.1f;
    float m_moveSpeed = 90.0f;

    PlayerPhysics m_physics;
    RaycastingPx m_raycast;

    bool m_jumpPressedLastFrame = false;
};

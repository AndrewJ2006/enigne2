#pragma once

#include "PlayerCamera.h"
#include "Physics.h"

class Player {
public:
    Player();

    bool InitPhysics();
    void Update(float deltaTime);

    // Public getter to access camera safely
    PlayerCamera& GetCamera() { return m_camera; }
    const PlayerCamera& GetCamera() const { return m_camera; }

private:
    PlayerCamera m_camera;
    PlayerPhysics m_physics;
    RaycastingPx m_raycast;
    bool m_jumpPressedLastFrame;

    static bool fPressedLastFrame;
};

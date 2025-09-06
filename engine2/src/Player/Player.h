#pragma once

#include "PlayerCamera.h"
#include "Physics.h"
#include <stdexcept>

class Player {
public:
    Player();

    bool InitPhysics();
    void Update(float deltaTime);

    PlayerCamera& GetCamera() { return m_camera; }

private:
    PlayerCamera m_camera;

    PlayerPhysics m_physics; 
    RaycastingPx m_raycast;   

    bool m_jumpPressedLastFrame = false;
    static bool fPressedLastFrame;
};

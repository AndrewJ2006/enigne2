#pragma once

#include "PlayerCamera.h"
#include "Camera.h"
#include "World.h"

class Game {
public:
    Game();

    void Init();
    void Update(float deltaTime);
    void Render();
    bool ShouldClose();

private:
    PlayerCamera m_playerCamera;
    Camera m_freeCamera;
    Camera* m_activeCamera = nullptr;

    bool m_cameraTogglePressed = false;

    World m_world;
};

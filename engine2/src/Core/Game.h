#pragma once
#include "World.h"
#include "Camera.h"  // Your camera class header

class Game {
public:
    Game();
    void Init();
    void Update(float deltaTime);
    void Render();
    bool ShouldClose();

private:
    World m_world;
    Camera m_camera;
};

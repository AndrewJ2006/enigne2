#pragma once
#include "Camera.h"

class Game {
public:
    Game();

    void Init();
    void Update(float deltaTime);
    void Render();
    bool ShouldClose();

private:
    Camera m_camera;
};

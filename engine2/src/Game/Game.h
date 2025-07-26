#ifndef GAME_H
#define GAME_H

#include "Player.h"
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
    Player m_player;
    PlayerCamera m_playerCamera;
    Camera m_freeCamera;

    Camera* m_activeCamera;

    bool m_cameraTogglePressed;
    World m_world;
};

#endif // GAME_H

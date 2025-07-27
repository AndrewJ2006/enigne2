#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "CameraEditor.h"
#include "Editor.h"
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
    CameraEditor m_freeCamera;   // Free camera for editor mode

    Camera* m_activeCamera = nullptr;  // Pointer to currently active camera

    bool m_cameraTogglePressed = false;
    World m_world;

    Editor m_editor;
};

#endif // GAME_H

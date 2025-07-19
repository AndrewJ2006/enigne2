#pragma once

#include "PlayerCamera.h"
#include "Camera.h"

class InputManager {
public:
    void SetActivePlayer(PlayerCamera* playerCamera);
    void SetActiveCamera(Camera* camera);

    void Update(float deltaTime);

private:
    PlayerCamera* m_playerCamera = nullptr;
    Camera* m_genericCamera = nullptr;
};

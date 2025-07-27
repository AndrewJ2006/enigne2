#pragma once

#include "Camera.h"

class PlayerCamera : public Camera {
public:
    PlayerCamera();

    // Override Update to handle WASD movement and mouse input
    void Update(float deltaTime) override;
};

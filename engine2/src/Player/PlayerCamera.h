#pragma once

#include "Camera.h"

class PlayerCamera : public Camera {
public:
    PlayerCamera();

    
    void Update(float deltaTime) override;
};

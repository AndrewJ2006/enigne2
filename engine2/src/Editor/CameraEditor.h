#pragma once

#include "Camera.h"

class CameraEditor : public Camera {
public:
    CameraEditor(glm::vec3 position = glm::vec3(0.0f, 5.0f, 5.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = -20.0f);

    void Update(float deltaTime) override;
};

#pragma once

#include "CameraEditor.h"

class PlayerCamera : public Camera {
public:
    PlayerCamera();

    // Public wrapper for protected updateCameraVectors
    void UpdateCameraVectors() { updateCameraVectors(); }

    // Expose protected members via getters if needed
    float GetYaw() const { return Yaw; }
    void SetYaw(float yaw) { Yaw = yaw; }

    float GetPitch() const { return Pitch; }
    void SetPitch(float pitch) { Pitch = pitch; }

    float GetMovementSpeed() const { return MovementSpeed; }
    float GetMouseSensitivity() const { return MouseSensitivity; }

    glm::vec3 GetPosition() const { return Position; }
    void SetPosition(const glm::vec3& position) { Position = position; }

    glm::vec3 GetFront() const { return Front; }
    glm::vec3 GetRight() const { return Right; }
};

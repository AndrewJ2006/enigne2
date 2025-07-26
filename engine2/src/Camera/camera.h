#pragma once

#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    // Constructors
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch);

    virtual ~Camera() = default;

    // Main update function: processes input internally
    virtual void Update(float deltaTime);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.0f) const;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void PerformRaycast();

    // Setters/getters
    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;

    void SetYaw(float yaw);
    float GetYaw() const;

    void SetPitch(float pitch);
    float GetPitch() const;

    void SetMovementSpeed(float speed);
    float GetMovementSpeed() const;

    void SetMouseSensitivity(float sensitivity);
    float GetMouseSensitivity() const;

    void SetZoom(float zoom);
    float GetZoom() const;

    void updateCameraVectors();

protected:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
};

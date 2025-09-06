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

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch);

    virtual ~Camera() = default;

    virtual void Update(float deltaTime);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);

    float GetYaw() const;
    void SetYaw(float yaw);

    float GetPitch() const;
    void SetPitch(float pitch);

    float GetMovementSpeed() const;
    void SetMovementSpeed(float speed);

    float GetMouseSensitivity() const;
    void SetMouseSensitivity(float sensitivity);

    float GetZoom() const;
    void SetZoom(float zoom);

    glm::vec3 GetFront() const;
    glm::vec3 GetRight() const;

    void UpdateCameraVectors();

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

    static constexpr float DEFAULT_SPEED = 2.5f;
    static constexpr float DEFAULT_SENSITIVITY = 0.1f;
    static constexpr float DEFAULT_ZOOM = 45.0f;
};

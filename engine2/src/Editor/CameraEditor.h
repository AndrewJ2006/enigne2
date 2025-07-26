#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

constexpr float DEFAULT_YAW = -90.0f;
constexpr float DEFAULT_PITCH = 0.0f;
constexpr float DEFAULT_SPEED = 3.5f;
constexpr float DEFAULT_SENSITIVITY = 0.1f;
constexpr float DEFAULT_ZOOM = 45.0f;

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void Update(float deltaTime);
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

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

    glm::vec3 GetFront() const { return Front; }

protected:
    void updateCameraVectors();

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

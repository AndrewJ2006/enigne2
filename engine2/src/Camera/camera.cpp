#include "Camera.h"
#include "Backend.h"
#include "Physics.h"      // Your physics manager and raycasting wrapper
#include "Door.h"         // Door class with ToggleOpenClose

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <algorithm>

using namespace physx;

extern std::vector<Door*> g_Doors;  // Your global door list

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Position(position),
    WorldUp(up),
    Yaw(yaw),
    Pitch(pitch),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM)
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ,
    float upX, float upY, float upZ,
    float yaw, float pitch)
    : Position(glm::vec3(posX, posY, posZ)),
    WorldUp(glm::vec3(upX, upY, upZ)),
    Yaw(yaw),
    Pitch(pitch),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM)
{
    updateCameraVectors();
}

void Camera::Update(float deltaTime) {
    // Keyboard input handled here
    if (Backend::IsKeyPressed(GLFW_KEY_W)) ProcessKeyboard(FORWARD, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_S)) ProcessKeyboard(BACKWARD, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_A)) ProcessKeyboard(LEFT, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_D)) ProcessKeyboard(RIGHT, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_E)) ProcessKeyboard(UP, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_Q)) ProcessKeyboard(DOWN, deltaTime);

    // Mouse movement input
    float mouseX, mouseY;
    Backend::GetMouseDelta(mouseX, mouseY);
    ProcessMouseMovement(mouseX, mouseY);

    // Raycast on pressing F key
    static bool fPressedLastFrame = false;
    bool fPressed = Backend::IsKeyPressed(GLFW_KEY_F);
    if (fPressed && !fPressedLastFrame) {
        PerformRaycast();
    }
    fPressedLastFrame = fPressed;
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const {
    return glm::perspective(glm::radians(Zoom), aspectRatio, nearPlane, farPlane);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)  Position += Front * velocity;
    if (direction == BACKWARD) Position -= Front * velocity;
    if (direction == LEFT)     Position -= Right * velocity;
    if (direction == RIGHT)    Position += Right * velocity;
    if (direction == UP)       Position += WorldUp * velocity;
    if (direction == DOWN)     Position -= WorldUp * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f)  Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f)  Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}

void Camera::PerformRaycast() {
    PxScene* scene = PhysicsManager::Get().GetScene();
    RaycastingPx raycaster(scene);

    PxVec3 origin(Position.x, Position.y, Position.z);
    glm::vec3 frontNorm = glm::normalize(Front);
    PxVec3 direction(frontNorm.x, frontNorm.y, frontNorm.z);

    PxRaycastBuffer hitBuffer;
    float maxDistance = 3.5f;

    if (raycaster.Raycast(origin, direction, maxDistance, hitBuffer)) {
        PxActor* hitActor = hitBuffer.block.actor;
        if (hitActor) {
            for (Door* door : g_Doors) {
                if (door && door->GetRigidActor() == hitActor) {
                    door->ToggleOpenClose();
                    break;
                }
            }
        }
    }
}

void Camera::SetPosition(const glm::vec3& position) {
    Position = position;
}

glm::vec3 Camera::GetPosition() const {
    return Position;
}

void Camera::SetYaw(float yaw) {
    Yaw = yaw;
    updateCameraVectors();
}

float Camera::GetYaw() const {
    return Yaw;
}

void Camera::SetPitch(float pitch) {
    Pitch = pitch;
    updateCameraVectors();
}

float Camera::GetPitch() const {
    return Pitch;
}

void Camera::SetMovementSpeed(float speed) {
    MovementSpeed = speed;
}

float Camera::GetMovementSpeed() const {
    return MovementSpeed;
}

void Camera::SetMouseSensitivity(float sensitivity) {
    MouseSensitivity = sensitivity;
}

float Camera::GetMouseSensitivity() const {
    return MouseSensitivity;
}

void Camera::SetZoom(float zoom) {
    Zoom = std::clamp(zoom, 1.0f, 45.0f);
}

float Camera::GetZoom() const {
    return Zoom;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

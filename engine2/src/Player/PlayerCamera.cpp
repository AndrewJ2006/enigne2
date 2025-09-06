#include "PlayerCamera.h"
#include "Backend.h"

PlayerCamera::PlayerCamera()
    : Camera(glm::vec3(0.0f, 1.75f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        0.0f) {
    MovementSpeed = 30.0f;
}

void PlayerCamera::Update(float deltaTime) {
    
    float mouseX, mouseY;
    Backend::GetMouseDelta(mouseX, mouseY);
    ProcessMouseMovement(mouseX, mouseY);
}

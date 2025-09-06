#include "CameraEditor.h"
#include "Backend.h"

CameraEditor::CameraEditor(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Camera(position, up, yaw, pitch) {
}

void CameraEditor::Update(float deltaTime) {
    if (Backend::IsKeyPressed(GLFW_KEY_W)) ProcessKeyboard(FORWARD, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_S)) ProcessKeyboard(BACKWARD, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_A)) ProcessKeyboard(LEFT, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_D)) ProcessKeyboard(RIGHT, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_E)) ProcessKeyboard(UP, deltaTime);
    if (Backend::IsKeyPressed(GLFW_KEY_Q)) ProcessKeyboard(DOWN, deltaTime);

    float mouseX, mouseY;
    Backend::GetMouseDelta(mouseX, mouseY);
    ProcessMouseMovement(mouseX, mouseY);
}

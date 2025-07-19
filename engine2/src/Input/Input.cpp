#include "Input.h"
#include "Backend.h"
#include <GLFW/glfw3.h>

void InputManager::SetActivePlayer(PlayerCamera* playerCamera) {
    m_playerCamera = playerCamera;
}

void InputManager::SetActiveCamera(Camera* camera) {
    m_genericCamera = camera;
}

void InputManager::Update(float deltaTime) {
    float mouseX = 0.0f, mouseY = 0.0f;
    Backend::GetMouseDelta(mouseX, mouseY);

    if (m_playerCamera) {
        // PlayerCamera still expects mouse deltas + deltaTime only
        m_playerCamera->Update(mouseX, mouseY, deltaTime);
    }
    else if (m_genericCamera) {
        // Poll keys
        bool w = Backend::IsKeyPressed(GLFW_KEY_W);
        bool s = Backend::IsKeyPressed(GLFW_KEY_S);
        bool a = Backend::IsKeyPressed(GLFW_KEY_A);
        bool d = Backend::IsKeyPressed(GLFW_KEY_D);
        bool q = Backend::IsKeyPressed(GLFW_KEY_Q);
        bool e = Backend::IsKeyPressed(GLFW_KEY_E);
        bool f = Backend::IsKeyPressed(GLFW_KEY_F);

        // Pass all inputs explicitly to generic camera
        m_genericCamera->UpdateFromInput(w, s, a, d, q, e, mouseX, mouseY, f, deltaTime);
    }
}

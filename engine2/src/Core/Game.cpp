#include "Game.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "Backend.h"
#include <stdexcept> // for std::runtime_error

Game::Game()
    : m_freeCamera(glm::vec3(0.0f, 5.0f, 5.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        -20.0f),
    m_cameraTogglePressed(false),  // Make sure this is initialized
    m_activeCamera(nullptr)
{
}

void Game::Init() {
    AssetManager::Init();
    Renderer::Init();
    m_world.Init();

    // Initialize physics for player camera and throw on failure
    if (!m_playerCamera.InitPhysics()) {
        throw std::runtime_error("Failed to initialize PlayerCamera physics.");
    }

    // Optional: Set player camera start position if needed
    // m_playerCamera.SetPosition(glm::vec3(0.0f, 1.75f, 3.0f));

    m_activeCamera = &m_playerCamera;
}

void Game::Update(float deltaTime) {
    float dx = 0.0f, dy = 0.0f;
    Backend::GetMouseDelta(dx, dy);

    // Handle camera toggle on 'C' key press with debounce
    if (Backend::IsKeyPressed(GLFW_KEY_C)) {
        if (!m_cameraTogglePressed) {
            if (m_activeCamera == &m_playerCamera) {
                m_activeCamera = static_cast<Camera*>(&m_freeCamera);
            }
            else {
                m_activeCamera = static_cast<Camera*>(&m_playerCamera);
            }
            m_cameraTogglePressed = true;
        }
    }
    else {
        m_cameraTogglePressed = false;
    }

    // Update active camera based on current mode
    if (m_activeCamera == &m_playerCamera) {
        m_playerCamera.Update(dx, dy, deltaTime);
    }
    else if (m_activeCamera == &m_freeCamera) {
        m_freeCamera.UpdateFromInput(deltaTime);
    }
    else {
        // Fallback if active camera is null (should not happen)
        m_activeCamera = &m_playerCamera;
    }

    m_world.Update(deltaTime);
}

void Game::Render() {
    float aspect = Backend::GetAspectRatio();

    if (!m_activeCamera) {
        // Defensive fallback
        return;
    }

    glm::mat4 view = m_activeCamera->GetViewMatrix();
    glm::mat4 projection = m_activeCamera->GetProjectionMatrix(aspect);

    Renderer::DrawScene(view, projection, m_world);
    m_world.Draw();
}

bool Game::ShouldClose() {
    return Backend::WindowShouldClose();
}

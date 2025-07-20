#include "Game.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "Backend.h"
#include <stdexcept>

Game::Game()
    : m_freeCamera(glm::vec3(0.0f, 5.0f, 5.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        -20.0f),
    m_cameraTogglePressed(false),
    m_activeCamera(nullptr)
{
}

void Game::Init() {
    AssetManager::Init();
    Renderer::Init();
    m_world.Init();

    if (!m_playerCamera.InitPhysics()) {
        throw std::runtime_error("Failed to initialize PlayerCamera physics.");
    }

    m_activeCamera = &m_playerCamera;
}

void Game::Update(float deltaTime) {
    // Handle camera toggle with debounce on 'C' key
    if (Backend::IsKeyPressed(GLFW_KEY_C)) {
        if (!m_cameraTogglePressed) {
            if (m_activeCamera == &m_playerCamera) {
                m_activeCamera = &m_freeCamera;
            }
            else {
                m_activeCamera = &m_playerCamera;
            }
            m_cameraTogglePressed = true;
        }
    }
    else {
        m_cameraTogglePressed = false;
    }

    // Update active camera
    if (m_activeCamera == &m_playerCamera) {
        m_playerCamera.Update(deltaTime);
    }
    else if (m_activeCamera == &m_freeCamera) {
        m_freeCamera.Update(deltaTime);
    }
    else {
        m_activeCamera = &m_playerCamera; // fallback safety
    }

    m_world.Update(deltaTime);
}

void Game::Render() {
    if (!m_activeCamera) return;

    float aspect = Backend::GetAspectRatio();
    glm::mat4 view = m_activeCamera->GetViewMatrix();
    glm::mat4 projection = m_activeCamera->GetProjectionMatrix(aspect);

    Renderer::DrawScene(view, projection, m_world);
    m_world.Draw();
}

bool Game::ShouldClose() {
    return Backend::WindowShouldClose();
}

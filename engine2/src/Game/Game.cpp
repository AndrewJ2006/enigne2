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
    m_activeCamera(nullptr),
    m_editor()
{
}

void Game::Init() {
    AssetManager::Init();
    Renderer::Init();
    m_world.Init();

    if (!m_player.InitPhysics()) {
        throw std::runtime_error("Failed to initialize Player physics.");
    }

    m_activeCamera = &(m_player.GetCamera());

    m_editor.SetCamera(m_activeCamera);
}

void Game::Update(float deltaTime) {
    if (Backend::IsKeyPressed(GLFW_KEY_C)) {
        if (!m_cameraTogglePressed) {
            if (m_activeCamera == &(m_player.GetCamera())) {
                m_activeCamera = &m_freeCamera;
            }
            else {
                m_activeCamera = &(m_player.GetCamera());
            }
            m_cameraTogglePressed = true;

            m_editor.SetCamera(m_activeCamera);
        }
    }
    else {
        m_cameraTogglePressed = false;
    }

    if (m_activeCamera == &(m_player.GetCamera())) {
        m_player.Update(deltaTime);
    }
    else if (m_activeCamera == &m_freeCamera) {
        m_freeCamera.Update(deltaTime);
    }
    else {
        m_activeCamera = &(m_player.GetCamera());
    }

    m_world.Update(deltaTime);
    m_editor.Update(deltaTime);
}

void Game::Render() {
    if (!m_activeCamera) return;

    float aspect = Backend::GetAspectRatio();
    glm::mat4 view = m_activeCamera->GetViewMatrix();
    glm::mat4 projection = m_activeCamera->GetProjectionMatrix(aspect, 0.1f, 100.0f);

    Renderer::DrawScene(view, projection, m_world);
    m_world.Draw();
}

bool Game::ShouldClose() {
    return Backend::WindowShouldClose();
}

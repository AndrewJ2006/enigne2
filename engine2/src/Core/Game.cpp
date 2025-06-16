#include "Game.h"
#include "Backend.h"
#include "Renderer.h"
#include <glm/glm.hpp>

Game::Game()
    : m_camera(glm::vec3(0.0f, 0.0f, 3.0f),   // Position
        glm::vec3(0.0f, 1.0f, 0.0f),   // Up vector
        -90.0f,                        // Yaw
        0.0f)                          // Pitch
{
}

void Game::Init() {
    // Any game initialization here
}

void Game::Update(float deltaTime) {
    m_camera.UpdateFromInput(deltaTime);
}

void Game::Render() {
    float aspect = Backend::GetAspectRatio();
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = m_camera.GetProjectionMatrix(aspect);

    Renderer::DrawScene(view, projection);
}

bool Game::ShouldClose() {
    return Backend::WindowShouldClose();
}

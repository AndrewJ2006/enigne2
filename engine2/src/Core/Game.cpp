#include "Game.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "Backend.h"

Game::Game()
    : m_camera(glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        0.0f) {
}

void Game::Init() {
    AssetManager::Init();
    Renderer::Init();
    m_world.Init();
}

void Game::Update(float deltaTime) {
    m_camera.UpdateFromInput(deltaTime);
    m_world.Update(deltaTime);
}

void Game::Render() {
    float aspect = Backend::GetAspectRatio();
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = m_camera.GetProjectionMatrix(aspect);

    Renderer::DrawScene(view, projection);
    m_world.Draw();
}

bool Game::ShouldClose() {
    return Backend::WindowShouldClose();
}

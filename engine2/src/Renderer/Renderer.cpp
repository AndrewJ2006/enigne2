#include "Renderer.h"
#include "AssetManager/AssetManager.h"
#include <glm/gtc/matrix_transform.hpp>

std::unique_ptr<Mesh> Renderer::s_planeMesh = nullptr;
std::unique_ptr<Shader> Renderer::s_shader = nullptr;

bool Renderer::Init() {
    const auto& vertices = AssetManager::GetCubeVertices();
    const auto& indices = AssetManager::GetCubeIndices();

    s_planeMesh = std::make_unique<Mesh>(vertices, indices);
    s_shader = std::make_unique<Shader>("Plane.vert", "Plane.frag");

    return s_planeMesh != nullptr && s_shader != nullptr;
}


void Renderer::Draw() {
    if (!s_planeMesh || !s_shader) return;

    s_shader->Use();
    glm::mat4 model = glm::mat4(1.0f);
    // Default camera/view setup for main.cpp (can customize later)
    glm::mat4 view = glm::lookAt(
        glm::vec3(1.0f, 1.0f, 2.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
    );
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    s_shader->SetMat4("model", model);
    s_shader->SetMat4("view", view);
    s_shader->SetMat4("projection", projection);

    s_planeMesh->Draw();
}

void Renderer::Shutdown() {
    s_planeMesh.reset();
    s_shader.reset();
}

// Optional if you want to keep DrawScene for other parts of your program (like Game class)
void Renderer::DrawScene(const glm::mat4& view, const glm::mat4& projection) {
    if (!s_planeMesh || !s_shader) return;

    s_shader->Use();

    glm::mat4 model = glm::mat4(1.0f);

    s_shader->SetMat4("model", model);
    s_shader->SetMat4("view", view);
    s_shader->SetMat4("projection", projection);

    s_planeMesh->Draw();
}

#include "Renderer.h"
#include "AssetManager.h"

std::unique_ptr<Mesh> Renderer::s_cubeMesh = nullptr;
std::unique_ptr<Shader> Renderer::s_shader = nullptr;

bool Renderer::Init() {
    const auto& vertices = AssetManager::GetCubeVertices();
    const auto& indices = AssetManager::GetCubeIndices();

    s_cubeMesh = std::make_unique<Mesh>(vertices, indices);
    s_shader = std::make_unique<Shader>("Plane.vert", "Plane.frag");

    return s_cubeMesh != nullptr && s_shader != nullptr;
}

void Renderer::DrawScene(const glm::mat4& view, const glm::mat4& projection) {
    if (!s_cubeMesh || !s_shader) return;

    s_shader->Use();

    glm::mat4 model = glm::mat4(1.0f);

    s_shader->SetMat4("model", model);
    s_shader->SetMat4("view", view);
    s_shader->SetMat4("projection", projection);

    s_cubeMesh->Draw();
}

void Renderer::Shutdown() {
    s_cubeMesh.reset();
    s_shader.reset();
}

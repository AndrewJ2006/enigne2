#include "Renderer/Renderer.h"
#include "AssetManager/AssetManager.h"
#include "Shader/Shader.h"
#include "Types/Mesh.h"

std::unique_ptr<Mesh> Renderer::s_cubeMesh = nullptr;
std::unique_ptr<Shader> Renderer::s_shader = nullptr;

bool Renderer::Init() {
    s_cubeMesh = std::make_unique<Mesh>(AssetManager::GetCubeVertices(), AssetManager::GetCubeIndices());
    s_shader = std::make_unique<Shader>("Plane.vert", "Plane.frag");
    return s_cubeMesh && s_shader;
}

void Renderer::DrawScene(const glm::mat4& view, const glm::mat4& projection) {
    if (!s_shader || !s_cubeMesh) return;

    s_shader->Use();
    s_shader->SetMat4("view", view);
    s_shader->SetMat4("projection", projection);
    // World::Draw() will handle drawing actual objects
}

void Renderer::Shutdown() {
    s_cubeMesh.reset();
    s_shader.reset();
}

Shader* Renderer::GetShader() {
    return s_shader.get();
}

Mesh* Renderer::GetCubeMesh() {
    return s_cubeMesh.get();
}

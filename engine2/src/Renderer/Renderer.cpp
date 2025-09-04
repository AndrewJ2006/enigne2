#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "World/World.h"

std::unique_ptr<Shader> Renderer::s_shader = nullptr;

bool Renderer::Init() {
    s_shader = std::make_unique<Shader>("Plane.vert", "Plane.frag");
    return s_shader != nullptr;
}

void Renderer::DrawScene(const glm::mat4& view, const glm::mat4& projection, World& world) {
    if (!s_shader) return;

    s_shader->Use();
    s_shader->SetMat4("view", view);
    s_shader->SetMat4("projection", projection);

    world.Draw(); 
}

void Renderer::Shutdown() {
    s_shader.reset();
}

Shader* Renderer::GetShader() {
    return s_shader.get();
}

#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::unique_ptr<Mesh> Renderer::s_planeMesh = nullptr;
std::unique_ptr<Shader> Renderer::s_shader = nullptr;

bool Renderer::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    s_planeMesh = std::make_unique<Mesh>(vertices, indices);
    s_shader = std::make_unique<Shader>("Plane.vert", "Plane.frag");
    return s_planeMesh && s_shader;
}

void Renderer::Draw() {
    if (!s_planeMesh || !s_shader) return;

    s_shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(1, 1, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
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

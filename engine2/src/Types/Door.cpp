#include "Door.h"
#include "CreateInfo.h" // <-- ADD THIS
#include "Types/Mesh.h" // Make sure Mesh is declared
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Door::Door(const DoorCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Door::Init() {
    float width = 1.0f;
    float height = 2.0f;
    glm::vec3 normal(0.0f, 0.0f, 1.0f);

    std::vector<Vertex> vertices = {
        { glm::vec3(0, 0, 0), normal, glm::vec2(0, 0) },
        { glm::vec3(width, 0, 0), normal, glm::vec2(1, 0) },
        { glm::vec3(width, height, 0), normal, glm::vec2(1, 1) },
        { glm::vec3(0, height, 0), normal, glm::vec2(0, 1) },
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Door::Update() {}

glm::vec3 Door::GetPosition() const { return m_createInfo.position; }
glm::vec3 Door::GetRotation() const { return m_createInfo.rotation; }
Mesh* Door::GetMesh() const { return m_mesh.get(); } // Optional: needed if used in World::Draw

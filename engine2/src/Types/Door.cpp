#include "Door.h"
#include "CreateInfo.h"
#include "Types/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Door::Door(const DoorCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Door::Init() {
    // Simple rectangle door at origin, size 1x2 units (width x height)
    float width = 1.0f;
    float height = 2.0f;

    glm::vec3 normal(0.0f, 0.0f, 1.0f);
    float offset = 0.01f; // Small offset to avoid z-fighting

    std::vector<Vertex> vertices = {
        { glm::vec3(0, 0, offset), normal, glm::vec2(0, 0) },
        { glm::vec3(width, 0, offset), normal, glm::vec2(1, 0) },
        { glm::vec3(width, height, offset), normal, glm::vec2(1, 1) },
        { glm::vec3(0, height, offset), normal, glm::vec2(0, 1) },
    };

    // Front face indices (CCW winding)
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    // Back face - flipped normal and reversed winding for double-sided
    glm::vec3 flippedNormal = -normal;
    unsigned int baseIndexBack = static_cast<unsigned int>(vertices.size());

    vertices.push_back({ glm::vec3(0, 0, offset), flippedNormal, glm::vec2(0, 0) });
    vertices.push_back({ glm::vec3(0, height, offset), flippedNormal, glm::vec2(0, 1) });
    vertices.push_back({ glm::vec3(width, height, offset), flippedNormal, glm::vec2(1, 1) });
    vertices.push_back({ glm::vec3(width, 0, offset), flippedNormal, glm::vec2(1, 0) });

    indices.push_back(baseIndexBack);
    indices.push_back(baseIndexBack + 1);
    indices.push_back(baseIndexBack + 2);
    indices.push_back(baseIndexBack);
    indices.push_back(baseIndexBack + 2);
    indices.push_back(baseIndexBack + 3);

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Door::Update() {}

glm::vec3 Door::GetPosition() const {
    return m_createInfo.position;
}

glm::vec3 Door::GetRotation() const {
    return m_createInfo.rotation;
}

Mesh* Door::GetMesh() const {
    return m_mesh.get();
}

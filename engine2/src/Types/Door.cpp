#include "Door.h"
#include <glm/gtc/matrix_transform.hpp>

Door::Door(const DoorCreateInfo& createInfo) : m_createInfo(createInfo) {}

void Door::Init() {
    glm::vec3 size = m_createInfo.size;  // width, height, depth
    glm::vec3 halfSize = size * 0.5f;

    // Define 8 corners of the rectangular prism door, centered around origin
    glm::vec3 p000 = { -halfSize.x, 0.0f, -halfSize.z };
    glm::vec3 p100 = { halfSize.x, 0.0f, -halfSize.z };
    glm::vec3 p110 = { halfSize.x, size.y, -halfSize.z };
    glm::vec3 p010 = { -halfSize.x, size.y, -halfSize.z };

    glm::vec3 p001 = { -halfSize.x, 0.0f, halfSize.z };
    glm::vec3 p101 = { halfSize.x, 0.0f, halfSize.z };
    glm::vec3 p111 = { halfSize.x, size.y, halfSize.z };
    glm::vec3 p011 = { -halfSize.x, size.y, halfSize.z };

    std::vector<Vertex> vertices = {
        // Front (+Z)
        {p001, {0, 0, 1}, {0, 0}}, {p101, {0, 0, 1}, {1, 0}}, {p111, {0, 0, 1}, {1, 1}}, {p011, {0, 0, 1}, {0, 1}},
        // Back (-Z)
        {p000, {0, 0, -1}, {0, 0}}, {p010, {0, 0, -1}, {1, 0}}, {p110, {0, 0, -1}, {1, 1}}, {p100, {0, 0, -1}, {0, 1}},
        // Left (-X)
        {p000, {-1, 0, 0}, {0, 0}}, {p001, {-1, 0, 0}, {1, 0}}, {p011, {-1, 0, 0}, {1, 1}}, {p010, {-1, 0, 0}, {0, 1}},
        // Right (+X)
        {p100, {1, 0, 0}, {0, 0}}, {p110, {1, 0, 0}, {1, 0}}, {p111, {1, 0, 0}, {1, 1}}, {p101, {1, 0, 0}, {0, 1}},
        // Top (+Y)
        {p010, {0, 1, 0}, {0, 0}}, {p011, {0, 1, 0}, {1, 0}}, {p111, {0, 1, 0}, {1, 1}}, {p110, {0, 1, 0}, {0, 1}},
        // Bottom (-Y)
        {p000, {0, -1, 0}, {0, 0}}, {p100, {0, -1, 0}, {1, 0}}, {p101, {0, -1, 0}, {1, 1}}, {p001, {0, -1, 0}, {0, 1}},
    };

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < 6; ++i) {
        unsigned int base = i * 4;
        indices.insert(indices.end(), {
            base, base + 1, base + 2,
            base + 2, base + 3, base
        });
    }

    // Transform (translation + rotation)
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_createInfo.position);
    transform = glm::rotate(transform, glm::radians(m_createInfo.rotation.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(m_createInfo.rotation.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(m_createInfo.rotation.z), glm::vec3(0, 0, 1));

    for (auto& v : vertices) {
        glm::vec4 pos = transform * glm::vec4(v.position, 1.0f);
        v.position = glm::vec3(pos);
        // Rotate normals if you want proper lighting:
        // v.normal = glm::mat3(transform) * v.normal;
    }

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Door::Update() {}

Mesh* Door::GetMesh() const {
    return m_mesh.get();
}

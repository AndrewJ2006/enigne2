#include "Plane.h"
#include <glm/gtc/matrix_transform.hpp>

Plane::Plane(const PlaneCreateInfo& createInfo) : m_createInfo(createInfo) {}

void Plane::Init() {
    glm::vec3 normal(0, 1, 0);

    // Front face (normal up)
    std::vector<Vertex> vertices = {
        { m_createInfo.p0, normal, glm::vec2(0.0f, 0.0f) },
        { m_createInfo.p1, normal, glm::vec2(1.0f, 0.0f) },
        { m_createInfo.p2, normal, glm::vec2(1.0f, 1.0f) },
        { m_createInfo.p3, normal, glm::vec2(0.0f, 1.0f) }
    };

    // Back face (normal down, reverse winding order)
    vertices.insert(vertices.end(), {
        { m_createInfo.p0, -normal, glm::vec2(0.0f, 0.0f) },
        { m_createInfo.p3, -normal, glm::vec2(1.0f, 0.0f) },
        { m_createInfo.p2, -normal, glm::vec2(1.0f, 1.0f) },
        { m_createInfo.p1, -normal, glm::vec2(0.0f, 1.0f) }
        });

    std::vector<unsigned int> indices = {
        0, 1, 2,   2, 3, 0,       // front face
        4, 5, 6,   6, 7, 4        // back face
    };

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Plane::Update() {}

Mesh* Plane::GetMesh() const {
    return m_mesh.get();
}

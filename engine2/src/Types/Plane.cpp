#include "Plane.h"
#include "CreateInfo.h" // <-- ADD THIS
#include "Types/Mesh.h"
#include <glm/glm.hpp>

Plane::Plane(const PlaneCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Plane::Init() {
    // Compute normal dynamically
    glm::vec3 edge1 = m_createInfo.p1 - m_createInfo.p0;
    glm::vec3 edge2 = m_createInfo.p2 - m_createInfo.p0;
    glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

    std::vector<Vertex> vertices = {
        { m_createInfo.p0, normal, glm::vec2(0.0f, 0.0f) },
        { m_createInfo.p1, normal, glm::vec2(1.0f, 0.0f) },
        { m_createInfo.p2, normal, glm::vec2(1.0f, 1.0f) },
        { m_createInfo.p3, normal, glm::vec2(0.0f, 1.0f) },
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    // Create back face (optional for double-sided)
    glm::vec3 flippedNormal = -normal;
    unsigned int baseIndexBack = static_cast<unsigned int>(vertices.size());

    vertices.push_back({ m_createInfo.p0, flippedNormal, glm::vec2(0.0f, 0.0f) });
    vertices.push_back({ m_createInfo.p3, flippedNormal, glm::vec2(0.0f, 1.0f) });
    vertices.push_back({ m_createInfo.p2, flippedNormal, glm::vec2(1.0f, 1.0f) });
    vertices.push_back({ m_createInfo.p1, flippedNormal, glm::vec2(1.0f, 0.0f) });

    indices.push_back(baseIndexBack);
    indices.push_back(baseIndexBack + 1);
    indices.push_back(baseIndexBack + 2);

    indices.push_back(baseIndexBack);
    indices.push_back(baseIndexBack + 2);
    indices.push_back(baseIndexBack + 3);

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Plane::Update() {}

glm::vec3 Plane::GetP0() const { return m_createInfo.p0; }
glm::vec3 Plane::GetP1() const { return m_createInfo.p1; }
glm::vec3 Plane::GetP2() const { return m_createInfo.p2; }
glm::vec3 Plane::GetP3() const { return m_createInfo.p3; }
const std::string& Plane::GetMaterial() const { return m_createInfo.material; }
Mesh* Plane::GetMesh() const { return m_mesh.get(); }


#define GLM_ENABLE_EXPERIMENTAL
#include "Plane.h"
#include "Utils.h"
#include <glm/gtc/matrix_transform.hpp>

Plane::Plane(const PlaneCreateInfo& createInfo) : m_createInfo(createInfo) {}

void Plane::Init() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Util::CreatePlaneMesh(vertices, indices, m_createInfo.p0, m_createInfo.p1, m_createInfo.p2, m_createInfo.p3);
    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Plane::Update() {}

Mesh* Plane::GetMesh() const {
    return m_mesh.get();
}
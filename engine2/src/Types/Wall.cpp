#include "Wall.h"
#include "CreateInfo.h" // <-- ADD THIS
#include "Types/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

Wall::Wall(const WallCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Wall::Init() {
    const auto& points = m_createInfo.points;
    float height = m_createInfo.height;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    size_t n = points.size();
    for (size_t i = 0; i < n; ++i) {
        glm::vec3 p0 = points[i];
        glm::vec3 p1 = points[(i + 1) % n];

        glm::vec3 p0_top = p0 + glm::vec3(0.0f, height, 0.0f);
        glm::vec3 p1_top = p1 + glm::vec3(0.0f, height, 0.0f);

        glm::vec3 edge = p1 - p0;
        glm::vec3 normal = glm::normalize(glm::cross(edge, glm::vec3(0.0f, 1.0f, 0.0f)));

        unsigned int baseIndex = static_cast<unsigned int>(vertices.size());

        vertices.push_back({ p0, normal, glm::vec2(0.0f, 0.0f) });
        vertices.push_back({ p1, normal, glm::vec2(1.0f, 0.0f) });
        vertices.push_back({ p1_top, normal, glm::vec2(1.0f, 1.0f) });
        vertices.push_back({ p0_top, normal, glm::vec2(0.0f, 1.0f) });

        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);

        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
    }

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Wall::Update() {}

const std::vector<glm::vec3>& Wall::GetPoints() const {
    return m_createInfo.points;
}

float Wall::GetHeight() const {
    return m_createInfo.height;
}

const std::string& Wall::GetMaterial() const {
    return m_createInfo.material;
}

Mesh* Wall::GetMesh() const { return m_mesh.get(); }

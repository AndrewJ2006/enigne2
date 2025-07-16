#include "Wall.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <memory>

Wall::Wall(const WallCreateInfo& createInfo) : m_createInfo(createInfo) {}

void Wall::Init() {
    std::vector<Vertex> allVertices;
    std::vector<unsigned int> allIndices;
    unsigned int indexOffset = 0;

    float thickness = 0.2f;

    for (size_t i = 0; i + 1 < m_createInfo.points.size(); ++i) {
        glm::vec3 p0 = m_createInfo.points[i];
        glm::vec3 p1 = m_createInfo.points[i + 1];
        float height = m_createInfo.height;

        glm::vec3 dir = glm::normalize(p1 - p0);             // Direction along wall
        glm::vec3 up(0, 1, 0);
        glm::vec3 normal = glm::normalize(glm::cross(up, dir)); // Perpendicular direction
        glm::vec3 offset = normal * (thickness * 0.5f);       // Half thickness offset

        // Define 8 corners of the rectangular prism
        glm::vec3 p000 = p0 - offset;                       // bottom front left
        glm::vec3 p100 = p1 - offset;                       // bottom front right
        glm::vec3 p110 = p1 + glm::vec3(0, height, 0) - offset;
        glm::vec3 p010 = p0 + glm::vec3(0, height, 0) - offset;

        glm::vec3 p001 = p0 + offset;
        glm::vec3 p101 = p1 + offset;
        glm::vec3 p111 = p1 + glm::vec3(0, height, 0) + offset;
        glm::vec3 p011 = p0 + glm::vec3(0, height, 0) + offset;

        std::vector<Vertex> verts = {
            // Front face
            {p000, normal, {0, 0}}, {p100, normal, {1, 0}}, {p110, normal, {1, 1}}, {p010, normal, {0, 1}},
            // Back face
            {p101, -normal, {0, 0}}, {p001, -normal, {1, 0}}, {p011, -normal, {1, 1}}, {p111, -normal, {0, 1}},
            // Left face
            {p001, {-1, 0, 0}, {0, 0}}, {p000, {-1, 0, 0}, {1, 0}}, {p010, {-1, 0, 0}, {1, 1}}, {p011, {-1, 0, 0}, {0, 1}},
            // Right face
            {p100, {1, 0, 0}, {0, 0}}, {p101, {1, 0, 0}, {1, 0}}, {p111, {1, 0, 0}, {1, 1}}, {p110, {1, 0, 0}, {0, 1}},
            // Top face
            {p010, {0, 1, 0}, {0, 0}}, {p110, {0, 1, 0}, {1, 0}}, {p111, {0, 1, 0}, {1, 1}}, {p011, {0, 1, 0}, {0, 1}},
            // Bottom face
            {p001, {0, -1, 0}, {0, 0}}, {p101, {0, -1, 0}, {1, 0}}, {p100, {0, -1, 0}, {1, 1}}, {p000, {0, -1, 0}, {0, 1}},
        };

        std::vector<unsigned int> inds;
        for (int face = 0; face < 6; ++face) {
            unsigned int base = indexOffset + face * 4;
            inds.insert(inds.end(), {
                base, base + 1, base + 2,
                base + 2, base + 3, base
                });
        }

        allVertices.insert(allVertices.end(), verts.begin(), verts.end());
        allIndices.insert(allIndices.end(), inds.begin(), inds.end());
        indexOffset += 24;
    }

    m_mesh = std::make_unique<Mesh>(allVertices, allIndices);
}

void Wall::Update() {}

Mesh* Wall::GetMesh() const {
    return m_mesh.get();
}

const std::string& Wall::GetMaterial() const {
    return m_createInfo.material;
}

void Wall::SetDoors(const std::vector<DoorCreateInfo>& doors) {
    // Door cutouts can go here later
}

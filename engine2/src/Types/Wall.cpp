
#define GLM_ENABLE_EXPERIMENTAL
#include "Wall.h"
#include "Utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <memory>

Wall::Wall(const WallCreateInfo& createInfo) : m_createInfo(createInfo) {}

void Wall::Init() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Util::CreatePrismWallMesh(vertices, indices, m_createInfo.points, m_createInfo.height);
    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Wall::Update() {}

Mesh* Wall::GetMesh() const {
    return m_mesh.get();
}

const std::string& Wall::GetMaterial() const {
    return m_createInfo.material;
}

void Wall::SetDoors(const std::vector<DoorCreateInfo>& doors) {
    
}
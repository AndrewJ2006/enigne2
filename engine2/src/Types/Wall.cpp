#include "wall.h"

Wall::Wall(const WallCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Wall::Init() {
    // Initialize wall, for example build mesh data based on m_createInfo
    // This is where you would create vertices, segments, etc.
}

void Wall::Update() {
    // Update wall logic, if needed
}

const std::vector<glm::vec3>& Wall::GetPoints() const {
    return m_createInfo.points;
}

float Wall::GetHeight() const {
    return m_createInfo.height;
}

const std::string& Wall::GetMaterial() const {
    return m_createInfo.material;
}

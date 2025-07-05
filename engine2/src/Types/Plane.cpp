#include "plane.h"

Plane::Plane(const PlaneCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Plane::Init() {
    // Initialize plane mesh or data based on m_createInfo
}

void Plane::Update() {
    // Update plane logic if needed
}

glm::vec3 Plane::GetP0() const { return m_createInfo.p0; }
glm::vec3 Plane::GetP1() const { return m_createInfo.p1; }
glm::vec3 Plane::GetP2() const { return m_createInfo.p2; }
glm::vec3 Plane::GetP3() const { return m_createInfo.p3; }
const std::string& Plane::GetMaterial() const { return m_createInfo.material; }

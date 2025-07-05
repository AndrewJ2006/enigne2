#include "door.h"

Door::Door(const DoorCreateInfo& createInfo)
    : m_createInfo(createInfo) {
}

void Door::Init() {
    // Initialize door object, spawn prefab, etc.
}

void Door::Update() {
    // Door logic update
}

glm::vec3 Door::GetPosition() const { return m_createInfo.position; }
glm::vec3 Door::GetRotation() const { return m_createInfo.rotation; }

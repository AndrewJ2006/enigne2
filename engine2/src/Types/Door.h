#pragma once
#include <glm/glm.hpp>
#include "JSON.h"  // For DoorCreateInfo

class Door {
public:
    Door(const DoorCreateInfo& createInfo);

    void Init();
    void Update();

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;

private:
    DoorCreateInfo m_createInfo;
};

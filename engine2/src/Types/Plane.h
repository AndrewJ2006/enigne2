#pragma once
#include <glm/glm.hpp>
#include "JSON.h"  // For PlaneCreateInfo

class Plane {
public:
    Plane(const PlaneCreateInfo& createInfo);

    void Init();
    void Update();

    glm::vec3 GetP0() const;
    glm::vec3 GetP1() const;
    glm::vec3 GetP2() const;
    glm::vec3 GetP3() const;
    const std::string& GetMaterial() const;

private:
    PlaneCreateInfo m_createInfo;
};

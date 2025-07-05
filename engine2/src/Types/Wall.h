#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "JSON.h"  // For WallCreateInfo

class Wall {
public:
    Wall(const WallCreateInfo& createInfo);

    void Init();
    void Update();

    const std::vector<glm::vec3>& GetPoints() const;
    float GetHeight() const;
    const std::string& GetMaterial() const;

private:
    WallCreateInfo m_createInfo;
};

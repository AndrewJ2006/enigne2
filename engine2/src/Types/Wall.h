#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include "CreateInfo.h"
#include "Types/Mesh.h"

class Wall {
public:
    Wall(const WallCreateInfo& createInfo);

    void Init();
    void Update();

    const std::vector<glm::vec3>& GetPoints() const;
    float GetHeight() const;
    const std::string& GetMaterial() const;
    Mesh* GetMesh() const;

private:
    WallCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};
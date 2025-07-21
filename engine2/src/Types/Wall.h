#pragma once

#include "CreateInfo.h"
#include "Mesh.h"   // Adjusted path
#include <memory>
#include <string>
#include <vector> // for std::vector

class Wall {
public:
    Wall(const WallCreateInfo& createInfo);

    void Init();
    void Update();

    Mesh* GetMesh() const;

    // Add GetMaterial and SetDoors declarations if used
    const std::string& GetMaterial() const;
    void SetDoors(const std::vector<DoorCreateInfo>& doors);

private:
    WallCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};

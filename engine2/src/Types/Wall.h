#pragma once

#include "CreateInfo.h"
#include "Types/Mesh.h"
#include <memory>
#include <string>
#include <vector> // for std::vector

class Wall {
public:
    Wall(const WallCreateInfo& createInfo);

    void Init();
    void Update();

    Mesh* GetMesh() const;

    const std::string& GetMaterial() const;           // Declare GetMaterial
    void SetDoors(const std::vector<DoorCreateInfo>& doors); // Declare SetDoors (optional)

private:
    WallCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};

#pragma once

#include "CreateInfo.h"
#include "Mesh.h"   
#include <memory>
#include <string>
#include <vector> 

class Wall {
public:
    Wall(const WallCreateInfo& createInfo);

    void Init();
    void Update();

    Mesh* GetMesh() const;

   
    const std::string& GetMaterial() const;
    void SetDoors(const std::vector<DoorCreateInfo>& doors);

private:
    WallCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};

#pragma once

#include "CreateInfo.h"
#include "Mesh.h"      
#include <memory>

class Plane {
public:
    Plane(const PlaneCreateInfo& createInfo);

    void Init();
    void Update();

    Mesh* GetMesh() const;

private:
    PlaneCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};

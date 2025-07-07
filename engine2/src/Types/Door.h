#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "CreateInfo.h"
#include "Types/Mesh.h"

class Door {
public:
    Door(const DoorCreateInfo& createInfo);

    void Init();
    void Update();

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    Mesh* GetMesh() const;

private:
    DoorCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};
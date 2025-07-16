#pragma once
#include "CreateInfo.h"
#include "Types/Mesh.h"
#include <memory>
#include <glm/glm.hpp> // for glm::vec3

class Door {
public:
    Door(const DoorCreateInfo& createInfo);
    void Init();
    void Update();
    Mesh* GetMesh() const;

    // Add these getters so World.cpp can access position and rotation
    glm::vec3 GetPosition() const { return m_createInfo.position; }
    glm::vec3 GetRotation() const { return m_createInfo.rotation; }

private:
    DoorCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
};

#pragma once
#include "CreateInfo.h"
#include "Types/Mesh.h"
#include <memory>
#include <glm/glm.hpp>
#include <PxPhysicsAPI.h>

class Door {
public:
    Door(const DoorCreateInfo& createInfo);

    void Init();
    void Update(float deltaTime);

    Mesh* GetMesh() const;

    glm::mat4 GetModelMatrix() const { return m_modelMatrix; }

private:
    DoorCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;

    physx::PxRigidDynamic* m_rigidActor = nullptr;
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
};

#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <PxPhysicsAPI.h>
#include "Mesh.h"
#include "CreateInfo.h"
#include "Transform.h"

class Door {
public:
    Door(const DoorCreateInfo& createInfo);

    void Init();
    void Draw();
    void Update(float deltaTime);
    void ToggleOpenClose();

    glm::mat4 GetModelMatrix() const;
    Mesh* GetMesh() const;
    physx::PxRigidActor* GetRigidActor() const;

    Transform GetTransform() const;

private:
    void UpdatePhysicsTransform();

    DoorCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
    physx::PxRigidDynamic* m_rigidActor = nullptr;

    glm::mat4 m_modelMatrix{ 1.0f };

    float m_currentAngle = 0.0f;
    float m_targetAngle = 0.0f;
    float m_rotationSpeed = 90.0f;
    bool m_isOpen = false;
};


extern std::vector<Door*> g_Doors;

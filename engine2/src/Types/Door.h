#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <PxPhysicsAPI.h>
#include "Mesh.h"
#include "CreateInfo.h"
#include <vector>

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

private:
    void UpdatePhysicsTransform();

    DoorCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
    physx::PxRigidDynamic* m_rigidActor = nullptr;

    glm::mat4 m_modelMatrix{ 1.0f };

    // Rotation state for smooth opening/closing
    float m_currentAngle = 0.0f;      // current rotation angle in degrees
    float m_targetAngle = 0.0f;       // target rotation angle in degrees
    float m_rotationSpeed = 90.0f;    // degrees per second
    bool m_isOpen = false;
};

// Declare global door vector here (define in one .cpp)
extern std::vector<Door*> g_Doors;
#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <PxPhysicsAPI.h>
#include "Mesh.h"
#include "CreateInfo.h"
#include "Transform.h"   // Include Transform for raycasting

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

    // New raycasting-related methods:
    Transform GetTransform() const;
    bool IsRayIntersecting(const glm::vec3& rayOrigin,
        const glm::vec3& rayDir,
        float maxDistance,
        glm::vec3& outHitPos,
        glm::vec3& outHitNormal);

private:
    void UpdatePhysicsTransform();

    DoorCreateInfo m_createInfo;
    std::unique_ptr<Mesh> m_mesh;
    physx::PxRigidDynamic* m_rigidActor = nullptr;

    glm::mat4 m_modelMatrix{ 1.0f };

    // Animation state
    float m_currentAngle = 0.0f;      // Current Y-axis rotation in degrees
    float m_targetAngle = 0.0f;       // Target Y-axis rotation in degrees
    float m_rotationSpeed = 90.0f;    // Degrees per second
    bool m_isOpen = false;
};

// Global door registry for raycasting
extern std::vector<Door*> g_Doors;

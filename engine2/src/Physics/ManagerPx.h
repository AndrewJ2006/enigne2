#pragma once

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>
#include <memory>

// Forward declaration for the collision system
class CollisionsPx;

class PhysicsManager {
public:
    static PhysicsManager& Get();

    void Init();
    void Step(float deltaTime);
    void Cleanup();

    physx::PxRigidDynamic* CreateDynamicBox(const glm::vec3& position, const glm::vec3& size, float mass);
    physx::PxRigidStatic* CreateStaticBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation);

    physx::PxPhysics* GetPhysics() const;
    physx::PxScene* GetScene() const;
    physx::PxMaterial* GetMaterial() const;
    physx::PxControllerManager* GetControllerManager() const;

    CollisionsPx* GetCollisionSystem() const { return m_collisions.get(); }

private:
    PhysicsManager() = default;
    ~PhysicsManager() = default;

    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    physx::PxFoundation* m_foundation = nullptr;
    physx::PxPhysics* m_physics = nullptr;
    physx::PxScene* m_scene = nullptr;
    physx::PxCpuDispatcher* m_dispatcher = nullptr;
    physx::PxControllerManager* m_controllerManager = nullptr;
    physx::PxMaterial* m_material = nullptr;

    std::unique_ptr<CollisionsPx> m_collisions;
};

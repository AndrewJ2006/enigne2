#pragma once

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>
#include <memory>

// Forward declarations of new subsystems
class ColliderPx;
class CollisionsPx;
class DebugPx;

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

    // Accessors for new systems
    CollisionsPx* GetCollisionSystem() const { return m_collisions.get(); }
    DebugPx* GetDebugSystem() const { return m_debug.get(); }

private:
    PhysicsManager() = default;
    ~PhysicsManager() = default;

    // Non-copyable
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    physx::PxFoundation* m_foundation = nullptr;
    physx::PxPhysics* m_physics = nullptr;
    physx::PxScene* m_scene = nullptr;
    physx::PxCpuDispatcher* m_dispatcher = nullptr;
    physx::PxControllerManager* m_controllerManager = nullptr;
    physx::PxMaterial* m_material = nullptr;

    std::unique_ptr<CollisionsPx> m_collisions;
    std::unique_ptr<DebugPx> m_debug;
};

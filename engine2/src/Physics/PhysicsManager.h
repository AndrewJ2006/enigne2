#pragma once

#include <PxPhysicsAPI.h>

class PhysicsManager {
public:
    static PhysicsManager& Get();

    void Init();
    void Step(float deltaTime);
    void Cleanup();

    physx::PxPhysics* GetPhysics() const { return m_physics; }
    physx::PxScene* GetScene() const { return m_scene; }
    physx::PxMaterial* GetMaterial() const { return m_material; }

private:
    PhysicsManager() = default;
    ~PhysicsManager() = default;

    // Delete copy constructor and assignment operator
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    physx::PxFoundation* m_foundation = nullptr;
    physx::PxPhysics* m_physics = nullptr;
    physx::PxDefaultCpuDispatcher* m_dispatcher = nullptr;
    physx::PxScene* m_scene = nullptr;
    physx::PxMaterial* m_material = nullptr;
};

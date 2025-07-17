#pragma once

#include <glm/glm.hpp>
#include <PxPhysicsAPI.h>

class PhysicsManager {
public:
    static PhysicsManager& Get();

    void Init();
    void Step(float deltaTime);
    void Cleanup();

    physx::PxPhysics* GetPhysics() const;
    physx::PxScene* GetScene() const;
    physx::PxMaterial* GetMaterial() const;

    physx::PxRigidDynamic* CreateDynamicBox(const glm::vec3& position, const glm::vec3& size, float mass);

    physx::PxRigidStatic* CreateStaticBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation);

    physx::PxControllerManager* GetControllerManager() const;

private:
    PhysicsManager() = default;
    ~PhysicsManager() = default;
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    physx::PxFoundation* m_foundation = nullptr;
    physx::PxPhysics* m_physics = nullptr;
    physx::PxDefaultCpuDispatcher* m_dispatcher = nullptr;
    physx::PxScene* m_scene = nullptr;
    physx::PxMaterial* m_material = nullptr;
    physx::PxControllerManager* m_controllerManager = nullptr;
};

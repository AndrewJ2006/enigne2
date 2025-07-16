#include "PhysicsManager.h"
#include <iostream>

using namespace physx;

PhysicsManager& PhysicsManager::Get() {
    static PhysicsManager instance;
    return instance;
}

void PhysicsManager::Init() {
    static PxDefaultErrorCallback gDefaultErrorCallback;
    static PxDefaultAllocator gDefaultAllocatorCallback;

    m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
    if (!m_foundation) {
        std::cerr << "PxCreateFoundation failed!" << std::endl;
        return;
    }

    m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale(), true);
    if (!m_physics) {
        std::cerr << "PxCreatePhysics failed!" << std::endl;
        return;
    }

    PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

    m_dispatcher = PxDefaultCpuDispatcherCreate(2);
    if (!m_dispatcher) {
        std::cerr << "PxDefaultCpuDispatcherCreate failed!" << std::endl;
        return;
    }

    sceneDesc.cpuDispatcher = m_dispatcher;
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;

    m_scene = m_physics->createScene(sceneDesc);
    if (!m_scene) {
        std::cerr << "createScene failed!" << std::endl;
        return;
    }

    m_material = m_physics->createMaterial(0.5f, 0.5f, 0.6f);
    if (!m_material) {
        std::cerr << "createMaterial failed!" << std::endl;
        return;
    }

    // ** Add ground plane here **
    PxRigidStatic* groundPlane = PxCreatePlane(*m_physics, PxPlane(0, 1, 0, 0), *m_material);
    if (!groundPlane) {
        std::cerr << "Failed to create ground plane!" << std::endl;
        return;
    }
    m_scene->addActor(*groundPlane);
}


void PhysicsManager::Step(float deltaTime) {
    if (m_scene) {
        m_scene->simulate(deltaTime);
        m_scene->fetchResults(true);
    }
}

void PhysicsManager::Cleanup() {
    if (m_scene) {
        m_scene->release();
        m_scene = nullptr;
    }
    if (m_dispatcher) {
        m_dispatcher->release();
        m_dispatcher = nullptr;
    }
    if (m_physics) {
        m_physics->release();
        m_physics = nullptr;
    }
    if (m_foundation) {
        m_foundation->release();
        m_foundation = nullptr;
    }
}

// *** Add the missing getter definitions here ***

physx::PxPhysics* PhysicsManager::GetPhysics() const {
    return m_physics;
}

physx::PxScene* PhysicsManager::GetScene() const {
    return m_scene;
}

physx::PxMaterial* PhysicsManager::GetMaterial() const {
    return m_material;
}

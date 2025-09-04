#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Physics.h>

#include <iostream>
#include <PxControllerManager.h>

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

    m_controllerManager = PxCreateControllerManager(*m_scene);
    if (!m_controllerManager) {
        std::cerr << "PxCreateControllerManager failed!" << std::endl;
        return;
    }

    m_material = m_physics->createMaterial(0.5f, 0.5f, 0.6f);
    if (!m_material) {
        std::cerr << "createMaterial failed!" << std::endl;
        return;
    }

    
    m_collisions = std::make_unique<CollisionsPx>(m_scene);
}

void PhysicsManager::Step(float deltaTime) {
    if (m_scene) {
        m_scene->simulate(deltaTime);
        m_scene->fetchResults(true);
    }
}

void PhysicsManager::Cleanup() {
    m_collisions.reset();

    if (m_scene) {
        m_scene->release();
        m_scene = nullptr;
    }
    if (m_controllerManager) {
        m_controllerManager->release();
        m_controllerManager = nullptr;
    }
    if (m_dispatcher) {
        delete m_dispatcher;
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

PxRigidDynamic* PhysicsManager::CreateDynamicBox(const glm::vec3& position, const glm::vec3& size, float mass) {
    if (!m_physics || !m_scene || !m_material) {
        std::cerr << "PhysicsManager not initialized properly." << std::endl;
        return nullptr;
    }

    PxTransform transform(PxVec3(position.x, position.y, position.z));
    PxBoxGeometry geometry(PxVec3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));

    PxRigidDynamic* body = PxCreateDynamic(*m_physics, transform, geometry, *m_material, mass);
    if (!body) {
        std::cerr << "Failed to create dynamic box!" << std::endl;
        return nullptr;
    }

    m_scene->addActor(*body);
    return body;
}

PxRigidStatic* PhysicsManager::CreateStaticBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation) {
    if (!m_physics || !m_scene || !m_material) {
        std::cerr << "PhysicsManager not initialized properly." << std::endl;
        return nullptr;
    }

    glm::quat rotQuat = glm::quat(glm::radians(rotation));
    PxTransform transform(
        PxVec3(position.x, position.y, position.z),
        PxQuat(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w)
    );

    PxBoxGeometry boxGeom(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

    PxRigidStatic* staticBox = m_physics->createRigidStatic(transform);
    if (!staticBox) {
        std::cerr << "Failed to create PxRigidStatic!" << std::endl;
        return nullptr;
    }

    PxShape* shape = m_physics->createShape(boxGeom, *m_material);
    if (!shape) {
        std::cerr << "Failed to create PxShape!" << std::endl;
        staticBox->release();
        return nullptr;
    }

    staticBox->attachShape(*shape);
    shape->release();

    m_scene->addActor(*staticBox);
    return staticBox;
}

physx::PxPhysics* PhysicsManager::GetPhysics() const {
    return m_physics;
}

physx::PxScene* PhysicsManager::GetScene() const {
    return m_scene;
}

physx::PxMaterial* PhysicsManager::GetMaterial() const {
    return m_material;
}

physx::PxControllerManager* PhysicsManager::GetControllerManager() const {
    return m_controllerManager;
}

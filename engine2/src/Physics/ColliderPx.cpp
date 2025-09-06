#define GLM_ENABLE_EXPERIMENTAL
#include <Physics.h>


#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace physx;

ColliderPx::ColliderPx(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation) {
    physx::PxPhysics* physics = PhysicsManager::Get().GetPhysics();
    physx::PxMaterial* material = PhysicsManager::Get().GetMaterial();

    if (!physics || !material) {
        std::cerr << "Physics or material not initialized!" << std::endl;
        m_rigidStatic = nullptr;
        return;
    }

    glm::quat rotQuat = glm::quat(glm::radians(rotation));

    PxTransform transform(
        PxVec3(position.x, position.y, position.z),
        PxQuat(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w)
    );

    PxBoxGeometry boxGeom(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

    m_rigidStatic = physics->createRigidStatic(transform);
    if (!m_rigidStatic) {
        std::cerr << "Failed to create PxRigidStatic!" << std::endl;
        return;
    }

    PxShape* shape = physics->createShape(boxGeom, *material);
    if (!shape) {
        std::cerr << "Failed to create PxShape!" << std::endl;
        m_rigidStatic->release();
        m_rigidStatic = nullptr;
        return;
    }

    m_rigidStatic->attachShape(*shape);
    shape->release();

    PxScene* scene = PhysicsManager::Get().GetScene();
    if (scene) {
        scene->addActor(*m_rigidStatic);
    }
}

ColliderPx::~ColliderPx() {
    if (m_rigidStatic) {
        m_rigidStatic->release();
        m_rigidStatic = nullptr;
    }
}

PxRigidStatic* ColliderPx::GetRigidStatic() const {
    return m_rigidStatic;
}

void ColliderPx::SetTransform(const glm::vec3& position, const glm::vec3& rotation) {
    if (!m_rigidStatic)
        return;

    glm::quat rotQuat = glm::quat(glm::radians(rotation));

    PxTransform transform(
        PxVec3(position.x, position.y, position.z),
        PxQuat(rotQuat.x, rotQuat.y, rotQuat.z, rotQuat.w)
    );

    m_rigidStatic->setGlobalPose(transform);
}

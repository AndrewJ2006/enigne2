#include "ColliderPx.h"
#include <iostream>

using namespace physx;

ColliderPx::ColliderPx(PxPhysics* physics, PxRigidActor* actor)
    : m_physics(physics), m_actor(actor), m_shape(nullptr)
{
}

ColliderPx::~ColliderPx() {
    if (m_shape) {
        m_shape->release();
        m_shape = nullptr;
    }
}

bool ColliderPx::CreateBox(const glm::vec3& size, const glm::vec3& localPosition) {
    if (!m_physics || !m_actor) return false;

    PxBoxGeometry boxGeom(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);
    PxTransform localPose(PxVec3(localPosition.x, localPosition.y, localPosition.z));

    m_shape = m_physics->createShape(boxGeom, *m_physics->createMaterial(0.5f, 0.5f, 0.6f), true);
    if (!m_shape) {
        std::cerr << "Failed to create box shape!" << std::endl;
        return false;
    }
    m_shape->setLocalPose(localPose);
    m_actor->attachShape(*m_shape);
    return true;
}

bool ColliderPx::CreateSphere(float radius, const glm::vec3& localPosition) {
    if (!m_physics || !m_actor) return false;

    PxSphereGeometry sphereGeom(radius);
    PxTransform localPose(PxVec3(localPosition.x, localPosition.y, localPosition.z));

    m_shape = m_physics->createShape(sphereGeom, *m_physics->createMaterial(0.5f, 0.5f, 0.6f), true);
    if (!m_shape) {
        std::cerr << "Failed to create sphere shape!" << std::endl;
        return false;
    }
    m_shape->setLocalPose(localPose);
    m_actor->attachShape(*m_shape);
    return true;
}

bool ColliderPx::CreateCapsule(float radius, float halfHeight, const glm::vec3& localPosition) {
    if (!m_physics || !m_actor) return false;

    PxCapsuleGeometry capsuleGeom(radius, halfHeight);
    PxTransform localPose(PxVec3(localPosition.x, localPosition.y, localPosition.z));

    m_shape = m_physics->createShape(capsuleGeom, *m_physics->createMaterial(0.5f, 0.5f, 0.6f), true);
    if (!m_shape) {
        std::cerr << "Failed to create capsule shape!" << std::endl;
        return false;
    }
    m_shape->setLocalPose(localPose);
    m_actor->attachShape(*m_shape);
    return true;
}

#include "CollisionPx.h"
#include <iostream>

using namespace physx;

CollisionsPx::CollisionEventCallback::CollisionEventCallback(CollisionsPx* parent)
    : m_parent(parent) {
}

void CollisionsPx::CollisionEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) {
    if (m_parent && m_parent->m_callback) {
        for (PxU32 i = 0; i < nbPairs; ++i) {
            m_parent->m_callback(pairs[i]);
        }
    }
}

void CollisionsPx::CollisionEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count) {
    // No-op
}

void CollisionsPx::CollisionEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {
    // No-op
}

void CollisionsPx::CollisionEventCallback::onWake(PxActor** actors, PxU32 count) {
    // No-op
}

void CollisionsPx::CollisionEventCallback::onSleep(PxActor** actors, PxU32 count) {
    // No-op
}

void CollisionsPx::CollisionEventCallback::onAdvance(
    const PxRigidBody* const* bodyBuffer,
    const PxTransform* poseBuffer,
    const PxU32 count)
{
    // No-op (required override in PhysX 5)
}

CollisionsPx::CollisionsPx(PxScene* scene)
    : m_scene(scene), m_callback(nullptr), m_eventCallback(nullptr)
{
    if (m_scene) {
        m_eventCallback = new CollisionEventCallback(this);
        m_scene->setSimulationEventCallback(m_eventCallback);
    }
}

CollisionsPx::~CollisionsPx() {
    if (m_scene) {
        m_scene->setSimulationEventCallback(nullptr);
    }
    delete m_eventCallback;
}

void CollisionsPx::SetCollisionCallback(CollisionCallback callback) {
    m_callback = callback;
}

void CollisionsPx::ProcessCollisions() {
    // Optional: implement manual collision processing if needed
}

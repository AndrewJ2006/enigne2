#pragma once

#include <PxPhysicsAPI.h>
#include <functional>

class CollisionsPx {
public:
    using CollisionCallback = std::function<void(const physx::PxContactPair&)>;

    CollisionsPx(physx::PxScene* scene);
    ~CollisionsPx();

    void SetCollisionCallback(CollisionCallback callback);
    void ProcessCollisions(); // Optional, placeholder

private:
    // Nested class handles PhysX collision events and forwards them
    class CollisionEventCallback : public physx::PxSimulationEventCallback {
    public:
        explicit CollisionEventCallback(CollisionsPx* parent);

        void onContact(const physx::PxContactPairHeader& pairHeader,
            const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;

        void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
        void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
        void onWake(physx::PxActor** actors, physx::PxU32 count) override;
        void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
        void onAdvance(const physx::PxRigidBody* const* bodyBuffer,
            const physx::PxTransform* poseBuffer,
            physx::PxU32 count) override;

    private:
        CollisionsPx* m_parent;
    };

    physx::PxScene* m_scene;
    CollisionCallback m_callback;
    CollisionEventCallback* m_eventCallback = nullptr;
};

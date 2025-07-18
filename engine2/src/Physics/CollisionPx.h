#pragma once
#include <PxPhysicsAPI.h>
#include <functional>

class CollisionsPx {
public:
    using CollisionCallback = std::function<void(const physx::PxContactPair&)>;

    explicit CollisionsPx(physx::PxScene* scene);
    ~CollisionsPx();

    void SetCollisionCallback(CollisionCallback callback);
    void ProcessCollisions();  // Optional, can be empty if unused

private:
    physx::PxScene* m_scene;
    CollisionCallback m_callback;

    class CollisionEventCallback : public physx::PxSimulationEventCallback {
    public:
        explicit CollisionEventCallback(CollisionsPx* parent);

        void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
        void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
        void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
        void onWake(physx::PxActor** actors, physx::PxU32 count) override;
        void onSleep(physx::PxActor** actors, physx::PxU32 count) override;

        // *** Must add this method to implement PxSimulationEventCallback ***
        void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override;

    private:
        CollisionsPx* m_parent;
    };

    CollisionEventCallback* m_eventCallback;
};

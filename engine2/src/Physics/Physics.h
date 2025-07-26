#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <PxPhysicsAPI.h>
#include <memory>
#include <functional>
#include <PxPhysicsAPI.h>

using namespace physx;

// ---------------- ColliderPx ----------------
class ColliderPx {
public:
    ColliderPx(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation);
    ~ColliderPx();

    physx::PxRigidStatic* GetRigidStatic() const;
    void SetTransform(const glm::vec3& position, const glm::vec3& rotation);

private:
    physx::PxRigidStatic* m_rigidStatic;
};

// ---------------- CollisionsPx ----------------
class CollisionsPx {
public:
    using CollisionCallback = std::function<void(const physx::PxContactPair&)>;

    explicit CollisionsPx(physx::PxScene* scene);
    ~CollisionsPx();

    void SetCollisionCallback(CollisionCallback callback);
    void ProcessCollisions();

private:
    class CollisionEventCallback;
    physx::PxScene* m_scene;
    CollisionCallback m_callback;
    CollisionEventCallback* m_eventCallback;

    class CollisionEventCallback : public physx::PxSimulationEventCallback {
    public:
        explicit CollisionEventCallback(CollisionsPx* parent);

        void onContact(const physx::PxContactPairHeader&, const physx::PxContactPair*, physx::PxU32) override;
        void onTrigger(physx::PxTriggerPair*, physx::PxU32) override;
        void onConstraintBreak(physx::PxConstraintInfo*, physx::PxU32) override;
        void onWake(physx::PxActor**, physx::PxU32) override;
        void onSleep(physx::PxActor**, physx::PxU32) override;
        void onAdvance(const physx::PxRigidBody* const*, const physx::PxTransform*, physx::PxU32) override;

    private:
        CollisionsPx* m_parent;
    };
};

// ---------------- PlayerPhysics ----------------
class PlayerPhysics {
public:
    PlayerPhysics();
    ~PlayerPhysics();

    bool Init(const physx::PxVec3& startPosition);
    void Move(const physx::PxVec3& direction);
    void Jump();
    void Update(float deltaTime);

    physx::PxController* GetController() const;
    bool IsOnGround() const;

private:
    physx::PxController* m_controller;
    float m_verticalVelocity;
    bool m_isJumping;
    physx::PxVec3 m_pendingMovement;
    float m_moveSpeed;
    const float gravity = -9.8f;
};

// ---------------- PhysicsManager ----------------
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

private:
    physx::PxFoundation* m_foundation = nullptr;
    physx::PxPhysics* m_physics = nullptr;
    physx::PxScene* m_scene = nullptr;
    physx::PxMaterial* m_material = nullptr;
    physx::PxCpuDispatcher* m_dispatcher = nullptr;
    physx::PxControllerManager* m_controllerManager = nullptr;
    std::unique_ptr<CollisionsPx> m_collisions;
};

// ---------------- RaycastingPx ----------------
class RaycastingPx {
public:
    explicit RaycastingPx(physx::PxScene* scene);
    bool Raycast(const physx::PxVec3& origin, const physx::PxVec3& direction, float maxDistance, physx::PxRaycastBuffer& hitBuffer);

private:
    physx::PxScene* m_scene;
};

// ---------------- ScenePx ----------------
class ScenePx {
public:
    ScenePx();
    ~ScenePx();

    bool Init();
    void CreateStaticFloor(); // <-- Move this from private to public
};
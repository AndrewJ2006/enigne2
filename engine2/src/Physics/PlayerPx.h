#pragma once
#include <PxPhysicsAPI.h>

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
    physx::PxCapsuleController* m_controller = nullptr;

    float m_verticalVelocity = 0.0f;   // Up/down velocity
    bool m_isJumping = false;

    physx::PxVec3 m_pendingMovement = physx::PxVec3(0.0f);
    const float gravity = -9.81f;
};

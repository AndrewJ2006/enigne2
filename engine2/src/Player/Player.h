#pragma once

#include <PxPhysicsAPI.h>
#include "PlayerPx.h"
#include "RaycastingPx.h"

class Player {
public:
    Player();
    ~Player();

    bool Init(const physx::PxVec3& startPosition);
    void Update(float deltaTime);

    // Move takes only one parameter: direction vector
    void Move(const physx::PxVec3& direction);

    void Jump();

    physx::PxVec3 GetPosition() const;
    physx::PxController* GetController() const;

private:
    PlayerPhysics m_physics;
    RaycastingPx m_raycast;
};

#pragma once

#include <PxPhysicsAPI.h>

class RaycastingPx {
public:
    RaycastingPx(physx::PxScene* scene);

    // Cast a ray from 'origin' in 'direction' for 'maxDistance'
    // Returns true if it hits something, outputs hit info
    bool Raycast(
        const physx::PxVec3& origin,
        const physx::PxVec3& direction,
        float maxDistance,
        physx::PxRaycastBuffer& hitBuffer);

private:
    physx::PxScene* m_scene = nullptr;
};

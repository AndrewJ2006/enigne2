#pragma once

#include <PxPhysicsAPI.h>

class RaycastingPx {
public:
    RaycastingPx(physx::PxScene* scene);

    bool Raycast(
        const physx::PxVec3& origin,
        const physx::PxVec3& direction,
        float maxDistance,
        physx::PxRaycastBuffer& hitBuffer);

private:
    physx::PxScene* m_scene = nullptr;
};
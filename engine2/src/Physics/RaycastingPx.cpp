#include "RaycastingPx.h"

using namespace physx;

RaycastingPx::RaycastingPx(PxScene* scene)
    : m_scene(scene)
{
}

bool RaycastingPx::Raycast(
    const PxVec3& origin,
    const PxVec3& direction,
    float maxDistance,
    PxRaycastBuffer& hitBuffer)
{
    if (!m_scene)
        return false;

    // Perform the raycast: true means we want any hit, closest hit will be stored in hitBuffer
    bool status = m_scene->raycast(
        origin,
        direction.getNormalized(),
        maxDistance,
        hitBuffer,
        PxHitFlag::eDEFAULT);

    return status && hitBuffer.hasBlock;
}

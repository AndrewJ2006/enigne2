#include <Physics.h>

using namespace physx;

RaycastingPx::RaycastingPx(PxScene* scene)
    : m_scene(scene) {
}

bool RaycastingPx::Raycast(const PxVec3& origin,
    const PxVec3& direction,
    float maxDistance,
    PxRaycastBuffer& hitBuffer) {
    if (!m_scene)
        return false;

    return m_scene->raycast(origin,
        direction.getNormalized(),
        maxDistance,
        hitBuffer,
        PxHitFlag::eDEFAULT)
        && hitBuffer.hasBlock;
}

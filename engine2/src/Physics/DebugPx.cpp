#include "DebugPx.h"
#include <iostream>

using namespace physx;

DebugPx::DebugPx(PxScene* scene)
    : m_scene(scene) {
}

DebugPx::~DebugPx() {}

void DebugPx::DrawDebug() {
    if (!m_scene) return;

    // Here you’d implement debug visualization, e.g. drawing collision shapes
    // using your rendering system or PhysX’s debug rendering if available.
    // For now just log for demonstration:
    std::cout << "DebugPx: Drawing physics debug info..." << std::endl;

    // Example: iterate over actors and print info
    PxU32 nbActors = m_scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
    if (nbActors == 0) return;

    PxActor** actors = new PxActor * [nbActors];
    m_scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, actors, nbActors);

    for (PxU32 i = 0; i < nbActors; ++i) {
        PxRigidActor* actor = static_cast<PxRigidActor*>(actors[i]);
        PxTransform pose = actor->getGlobalPose();
        std::cout << "Actor at position: (" << pose.p.x << ", " << pose.p.y << ", " << pose.p.z << ")" << std::endl;
    }

    delete[] actors;
}

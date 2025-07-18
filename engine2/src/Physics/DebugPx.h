#pragma once
#include <PxPhysicsAPI.h>

class DebugPx {
public:
    DebugPx(physx::PxScene* scene);
    ~DebugPx();

    void DrawDebug();

private:
    physx::PxScene* m_scene;
};

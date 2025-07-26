#include "Physics.h"

#include <iostream>
#include <PxPhysicsAPI.h>

using namespace physx;

ScenePx::ScenePx() = default;
ScenePx::~ScenePx() = default;

bool ScenePx::Init() {
    CreateStaticFloor();
    return true;
}

void ScenePx::CreateStaticFloor() {
    PhysicsManager& physicsMgr = PhysicsManager::Get();
    PxPhysics* physics = physicsMgr.GetPhysics();
    PxScene* scene = physicsMgr.GetScene();
    PxMaterial* material = physicsMgr.GetMaterial();

    if (!physics || !scene || !material) {
        std::cerr << "PhysX not initialized properly in ScenePx::CreateStaticFloor()" << std::endl;
        return;
    }

    PxRigidStatic* floorPlane = PxCreatePlane(*physics, PxPlane(0, 1, 0, 0), *material);
    if (!floorPlane) {
        std::cerr << "Failed to create PhysX floor plane" << std::endl;
        return;
    }

    scene->addActor(*floorPlane);
}

#include <PxPhysicsAPI.h>

int main() {
    static physx::PxDefaultAllocator      allocator;
    static physx::PxDefaultErrorCallback  errorCallback;

    physx::PxFoundation* foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
    physx::PxPhysics* physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale());

    physics->release();
    foundation->release();

    return 0;
}

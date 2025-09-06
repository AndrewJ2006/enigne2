#include "Utils.h"
#include "Door.h"
#include <PxPhysicsAPI.h>
#include "Physics.h"

using namespace physx;


extern std::vector<Door*> g_Doors;

namespace Util {

    Door* RaycastForDoor(PxScene* scene, const glm::vec3& origin, const glm::vec3& direction, float maxDistance) {
        RaycastingPx raycaster(scene);

        PxVec3 pxOrigin(origin.x, origin.y, origin.z);
        PxVec3 pxDirection = PxVec3(direction.x, direction.y, direction.z).getNormalized();

        PxRaycastBuffer hitBuffer;

        if (raycaster.Raycast(pxOrigin, pxDirection, maxDistance, hitBuffer)) {
            PxActor* hitActor = hitBuffer.block.actor;
            if (hitActor) {
                for (Door* door : g_Doors) {
                    if (door && door->GetRigidActor() == hitActor) {
                        return door;
                    }
                }
            }
        }
        return nullptr;
    }

}

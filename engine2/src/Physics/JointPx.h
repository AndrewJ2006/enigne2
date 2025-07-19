#pragma once

#include <PxPhysicsAPI.h>

class JointPx {
public:
    JointPx();
    ~JointPx();

    bool CreateHingedDoor(physx::PxPhysics* physics, physx::PxScene* scene,
        physx::PxMaterial* material,
        const physx::PxVec3& position, const physx::PxVec3& size);

    void SetDoorAngle(float angle);
    physx::PxRigidDynamic* GetDoorActor() const;

private:
    physx::PxRigidDynamic* m_door = nullptr;
    physx::PxRevoluteJoint* m_joint = nullptr;
};

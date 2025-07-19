#include "JointPx.h"

using namespace physx;

JointPx::JointPx() = default;
JointPx::~JointPx() = default;

bool JointPx::CreateHingedDoor(PxPhysics* physics, PxScene* scene,
    PxMaterial* material, const PxVec3& position, const PxVec3& size) {
    if (!physics || !scene || !material) return false;

    PxTransform doorPose(position);

    m_door = physics->createRigidDynamic(doorPose);
    PxShape* doorShape = physics->createShape(PxBoxGeometry(size), *material);
    m_door->attachShape(*doorShape);
    PxRigidBodyExt::updateMassAndInertia(*m_door, 10.0f);
    scene->addActor(*m_door);

    // Create anchor
    PxRigidStatic* anchor = physics->createRigidStatic(PxTransform(position));
    scene->addActor(*anchor);

    m_joint = PxRevoluteJointCreate(*physics, anchor, PxTransform(PxVec3(0, 0, 0)),
        m_door, PxTransform(PxVec3(0, 0, 0)));

    if (!m_joint) return false;

    m_joint->setLimit(PxJointAngularLimitPair(-PxPi / 2, PxPi / 2));
    m_joint->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
    return true;
}

void JointPx::SetDoorAngle(float angle) {
    if (m_joint) {
        m_joint->setDriveVelocity(angle); // Note: consider adding damping and drive force if needed
    }
}

PxRigidDynamic* JointPx::GetDoorActor() const {
    return m_door;
}

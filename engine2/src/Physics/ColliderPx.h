#pragma once
#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

class ColliderPx {
public:
    enum class Type {
        Box,
        Sphere,
        Capsule
        // Add more types as needed
    };

    ColliderPx(physx::PxPhysics* physics, physx::PxRigidActor* actor);
    ~ColliderPx();

    bool CreateBox(const glm::vec3& size, const glm::vec3& localPosition = glm::vec3(0));
    bool CreateSphere(float radius, const glm::vec3& localPosition = glm::vec3(0));
    bool CreateCapsule(float radius, float halfHeight, const glm::vec3& localPosition = glm::vec3(0));

private:
    physx::PxPhysics* m_physics;
    physx::PxRigidActor* m_actor;
    physx::PxShape* m_shape;
};

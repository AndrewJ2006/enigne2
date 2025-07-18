#pragma once

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>
#include <memory>

class ColliderPx {
public:
    // Constructor for static box collider
    ColliderPx(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation);

    ~ColliderPx();

    // Get the underlying PhysX rigid static actor
    physx::PxRigidStatic* GetRigidStatic() const;

    // Optionally, update transform (if needed)
    void SetTransform(const glm::vec3& position, const glm::vec3& rotation);

private:
    physx::PxRigidStatic* m_rigidStatic = nullptr;
};

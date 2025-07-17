#define GLM_ENABLE_EXPERIMENTAL
#include "Door.h"
#include "PhysicsManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <cmath>

std::vector<Door*> g_Doors;

Door::Door(const DoorCreateInfo& createInfo)
    : m_createInfo(createInfo),
    m_mesh(std::make_unique<Mesh>()),
    m_currentAngle(0.0f),
    m_targetAngle(0.0f),
    m_rotationSpeed(90.0f),
    m_isOpen(false)
{
}

void Door::Init() {
    glm::vec3 size = m_createInfo.size;
    glm::vec3 position = m_createInfo.position;
    position.y += size.y * 0.5f;  // Raise door so it sits on the floor

    // Create mesh with door size and color
    m_mesh->Create(size, glm::vec3(1.0f, 0.3f, 0.0f));

    // Create kinematic dynamic actor for the door
    physx::PxPhysics* physics = PhysicsManager::Get().GetPhysics();
    physx::PxMaterial* material = PhysicsManager::Get().GetMaterial();

    if (!physics || !material) {
        std::cerr << "Physics or material not initialized!" << std::endl;
        return;
    }

    // Compute initial pose for the door
    float halfWidth = size.x * 0.5f;

    // Door hinge is at left edge, so initial position offset accordingly
    glm::vec3 hingePosition = position + glm::vec3(-halfWidth, 0.0f, 0.0f);

    physx::PxTransform doorPose(
        physx::PxVec3(hingePosition.x, hingePosition.y, hingePosition.z),
        physx::PxQuat(0, physx::PxVec3(0, 1, 0))
    );

    // Create PxBoxGeometry sized as door size
    physx::PxBoxGeometry boxGeom(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

    // Create kinematic dynamic actor
    m_rigidActor = physics->createRigidDynamic(doorPose);
    if (!m_rigidActor) {
        std::cerr << "Failed to create PxRigidDynamic for door!" << std::endl;
        return;
    }

    physx::PxRigidDynamic* dynamicActor = static_cast<physx::PxRigidDynamic*>(m_rigidActor);

    // Add shape to actor
    physx::PxShape* shape = physics->createShape(boxGeom, *material, true);
    if (!shape) {
        std::cerr << "Failed to create shape for door!" << std::endl;
        m_rigidActor->release();
        m_rigidActor = nullptr;
        return;
    }
    dynamicActor->attachShape(*shape);
    shape->release();

    // Set kinematic flag so we can manually move the door
    dynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);

    // Disable gravity and other dynamics
    dynamicActor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

    // Add the door actor to the PhysX scene
    physx::PxScene* scene = PhysicsManager::Get().GetScene();
    if (scene)
        scene->addActor(*m_rigidActor);

    // Set initial model matrix for rendering (door closed)
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, size);
    m_modelMatrix = transform;
    m_mesh->SetModelMatrix(transform);
}

void Door::Draw() {
    if (m_mesh) {
        m_mesh->Draw();
    }
}

void Door::Update(float deltaTime) {
    if (std::abs(m_currentAngle - m_targetAngle) > 0.1f) {
        float direction = (m_targetAngle > m_currentAngle) ? 1.0f : -1.0f;
        m_currentAngle += direction * m_rotationSpeed * deltaTime;

        if ((direction > 0 && m_currentAngle > m_targetAngle) ||
            (direction < 0 && m_currentAngle < m_targetAngle)) {
            m_currentAngle = m_targetAngle;
        }

        glm::vec3 position = m_createInfo.position;
        position.y += m_createInfo.size.y * 0.5f;
        float halfWidth = m_createInfo.size.x * 0.5f;

        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, position);

        // Move pivot to left edge (hinge)
        transform = glm::translate(transform, glm::vec3(-halfWidth, 0.0f, 0.0f));

        // Rotate door around hinge
        transform = glm::rotate(transform, glm::radians(m_currentAngle), glm::vec3(0, 1, 0));

        // Move pivot back
        transform = glm::translate(transform, glm::vec3(halfWidth, 0.0f, 0.0f));

        transform = glm::scale(transform, m_createInfo.size);

        m_modelMatrix = transform;
        m_mesh->SetModelMatrix(m_modelMatrix);

        // Update the physics actor transform (kinematic target)
        UpdatePhysicsTransform();
    }
}

void Door::ToggleOpenClose() {
    if (m_targetAngle < 1.0f) {
        m_targetAngle = 90.0f;  // Open door (rotate 90 degrees)
        m_isOpen = true;
    }
    else {
        m_targetAngle = 0.0f;   // Close door (rotate 0 degrees)
        m_isOpen = false;
    }
    std::cout << "Door is now " << (m_isOpen ? "Open" : "Closed") << std::endl;
}

void Door::UpdatePhysicsTransform() {
    if (!m_rigidActor)
        return;

    glm::vec3 position = m_createInfo.position;
    position.y += m_createInfo.size.y * 0.5f;
    float halfWidth = m_createInfo.size.x * 0.5f;

    // Hinge position in world space
    glm::vec3 hingePos = position + glm::vec3(-halfWidth, 0.0f, 0.0f);

    // Rotation in radians
    float radians = glm::radians(m_currentAngle);
    glm::quat rotationQuat = glm::angleAxis(radians, glm::vec3(0, 1, 0));

    // Calculate door center position based on hinge + rotated offset
    glm::vec3 offset = rotationQuat * glm::vec3(halfWidth, 0.0f, 0.0f);
    glm::vec3 finalPos = hingePos + offset;

    physx::PxQuat pxRot(radians, physx::PxVec3(0, 1, 0));
    physx::PxTransform newTransform(
        physx::PxVec3(finalPos.x, finalPos.y, finalPos.z),
        pxRot
    );

    physx::PxRigidDynamic* dynActor = static_cast<physx::PxRigidDynamic*>(m_rigidActor);
    dynActor->setKinematicTarget(newTransform);
}

glm::mat4 Door::GetModelMatrix() const {
    return m_modelMatrix;
}

Mesh* Door::GetMesh() const {
    return m_mesh.get();
}

physx::PxRigidActor* Door::GetRigidActor() const {
    return m_rigidActor;
}

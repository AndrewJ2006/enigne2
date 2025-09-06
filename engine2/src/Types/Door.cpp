#include "Door.h"
#include "Physics.h"
#include "Utils.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <algorithm>

std::vector<Door*> g_Doors;

Door::Door(const DoorCreateInfo& createInfo)
    : m_createInfo(createInfo),
    m_mesh(std::make_unique<Mesh>()),
    m_currentAngle(0.0f),
    m_targetAngle(0.0f),
    m_rotationSpeed(90.0f),
    m_isOpen(false),
    m_rigidActor(nullptr)
{
}

void Door::Init() {
    glm::vec3 size = m_createInfo.size;
    glm::vec3 position = m_createInfo.position; 

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Util::CreateCubeMesh(vertices, indices, glm::vec3(1.0f, 0.3f, 0.0f));
    m_mesh = std::make_unique<Mesh>(vertices, indices);

    physx::PxPhysics* physics = PhysicsManager::Get().GetPhysics();
    physx::PxMaterial* material = PhysicsManager::Get().GetMaterial();

    if (!physics || !material) {
        std::cerr << "Physics or material not initialized!" << std::endl;
        return;
    }

    float halfWidth = size.x * 0.5f;
    float halfHeight = size.y * 0.5f;
    float halfDepth = size.z * 0.5f;

    
    glm::vec3 hingePos = position + glm::vec3(-halfWidth, 0.0f, 0.0f);

  
    physx::PxTransform hingeTransform(
        physx::PxVec3(hingePos.x, hingePos.y + halfHeight, hingePos.z),
        physx::PxQuat(0, physx::PxVec3(0, 1, 0))
    );

    physx::PxBoxGeometry boxGeom(halfWidth, halfHeight, halfDepth);

    m_rigidActor = physics->createRigidDynamic(hingeTransform);
    if (!m_rigidActor) {
        std::cerr << "Failed to create PxRigidDynamic for door!" << std::endl;
        return;
    }

    physx::PxRigidDynamic* dynamicActor = static_cast<physx::PxRigidDynamic*>(m_rigidActor);

    
    physx::PxTransform shapeLocalPose(physx::PxVec3(halfWidth, halfHeight, 0.0f));

    physx::PxShape* shape = physics->createShape(boxGeom, *material, true);
    if (!shape) {
        std::cerr << "Failed to create shape for door!" << std::endl;
        m_rigidActor->release();
        m_rigidActor = nullptr;
        return;
    }

    shape->setLocalPose(shapeLocalPose);
    dynamicActor->attachShape(*shape);
    shape->release();

    dynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
    dynamicActor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
    dynamicActor->userData = this;

    physx::PxScene* scene = PhysicsManager::Get().GetScene();
    if (scene)
        scene->addActor(*m_rigidActor);

    if (std::find(g_Doors.begin(), g_Doors.end(), this) == g_Doors.end()) {
        g_Doors.push_back(this);
    }

    
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, position + glm::vec3(0.0f, halfHeight, 0.0f));
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
        float halfWidth = m_createInfo.size.x * 0.5f;
        float halfHeight = m_createInfo.size.y * 0.5f;

        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, position + glm::vec3(0.0f, halfHeight, 0.0f));
        transform = glm::translate(transform, glm::vec3(-halfWidth, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(m_currentAngle), glm::vec3(0, 1, 0));
        transform = glm::translate(transform, glm::vec3(halfWidth, 0.0f, 0.0f));
        transform = glm::scale(transform, m_createInfo.size);

        m_modelMatrix = transform;
        m_mesh->SetModelMatrix(m_modelMatrix);

        UpdatePhysicsTransform();
    }
}

void Door::ToggleOpenClose() {
    m_targetAngle = (m_targetAngle < 1.0f) ? 90.0f : 0.0f;
    m_isOpen = (m_targetAngle > 1.0f);

    std::cout << "Door is now " << (m_isOpen ? "Open" : "Closed") << std::endl;
}

void Door::UpdatePhysicsTransform() {
    if (!m_rigidActor) return;

    glm::vec3 position = m_createInfo.position; 
    float halfWidth = m_createInfo.size.x * 0.5f;
    float halfHeight = m_createInfo.size.y * 0.5f;

  
    glm::vec3 hingePos = position + glm::vec3(-halfWidth, halfHeight, 0.0f);

    float radians = glm::radians(m_currentAngle);
    physx::PxQuat pxRot(radians, physx::PxVec3(0, 1, 0));

    physx::PxTransform newTransform(
        physx::PxVec3(hingePos.x, hingePos.y, hingePos.z),
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

Transform Door::GetTransform() const {
    Transform t;
    t.from_mat4(m_modelMatrix);
    return t;
}

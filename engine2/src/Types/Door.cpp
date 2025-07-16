#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Door.h"
#include "PhysicsManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace physx;

Door::Door(const DoorCreateInfo& createInfo) : m_createInfo(createInfo) {}

void Door::Init() {
    glm::vec3 size = m_createInfo.size;  // width, height, depth
    glm::vec3 halfSize = size * 0.5f;

    // Mesh geometry centered
    glm::vec3 p000 = { -halfSize.x, 0.0f, -halfSize.z };
    glm::vec3 p100 = { halfSize.x, 0.0f, -halfSize.z };
    glm::vec3 p110 = { halfSize.x, size.y, -halfSize.z };
    glm::vec3 p010 = { -halfSize.x, size.y, -halfSize.z };
    glm::vec3 p001 = { -halfSize.x, 0.0f,  halfSize.z };
    glm::vec3 p101 = { halfSize.x, 0.0f,  halfSize.z };
    glm::vec3 p111 = { halfSize.x, size.y,  halfSize.z };
    glm::vec3 p011 = { -halfSize.x, size.y,  halfSize.z };

    std::vector<Vertex> vertices = {
        // Front (+Z)
        {p001, {0, 0, 1}, {0, 0}}, {p101, {0, 0, 1}, {1, 0}}, {p111, {0, 0, 1}, {1, 1}}, {p011, {0, 0, 1}, {0, 1}},
        // Back (-Z)
        {p000, {0, 0, -1}, {0, 0}}, {p010, {0, 0, -1}, {1, 0}}, {p110, {0, 0, -1}, {1, 1}}, {p100, {0, 0, -1}, {0, 1}},
        // Left (-X)
        {p000, {-1, 0, 0}, {0, 0}}, {p001, {-1, 0, 0}, {1, 0}}, {p011, {-1, 0, 0}, {1, 1}}, {p010, {-1, 0, 0}, {0, 1}},
        // Right (+X)
        {p100, {1, 0, 0}, {0, 0}}, {p110, {1, 0, 0}, {1, 0}}, {p111, {1, 0, 0}, {1, 1}}, {p101, {1, 0, 0}, {0, 1}},
        // Top (+Y)
        {p010, {0, 1, 0}, {0, 0}}, {p011, {0, 1, 0}, {1, 0}}, {p111, {0, 1, 0}, {1, 1}}, {p110, {0, 1, 0}, {0, 1}},
        // Bottom (-Y)
        {p000, {0, -1, 0}, {0, 0}}, {p100, {0, -1, 0}, {1, 0}}, {p101, {0, -1, 0}, {1, 1}}, {p001, {0, -1, 0}, {0, 1}},
    };

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < 6; ++i) {
        unsigned int base = i * 4;
        indices.insert(indices.end(), {
            base, base + 1, base + 2,
            base + 2, base + 3, base
            });
    }

    m_mesh = std::make_unique<Mesh>(vertices, indices);

    // === PhysX Setup ===
    PhysicsManager& physicsMgr = PhysicsManager::Get();
    PxPhysics* physics = physicsMgr.GetPhysics();
    PxScene* scene = physicsMgr.GetScene();
    PxMaterial* material = physicsMgr.GetMaterial();

    if (!physics || !scene || !material) {
        std::cerr << "PhysX not initialized properly in Door::Init()" << std::endl;
        return;
    }

    // Create actor at CENTER of door
    PxTransform actorTransform(PxVec3(
        m_createInfo.position.x,
        m_createInfo.position.y,
        m_createInfo.position.z
    ));

    m_rigidActor = physics->createRigidDynamic(actorTransform);
    if (!m_rigidActor) {
        std::cerr << "Failed to create PxRigidDynamic for door" << std::endl;
        return;
    }

    // Offset collision box to the RIGHT so it hinges on the left
    PxBoxGeometry boxGeom(halfSize.x, halfSize.y, halfSize.z);
    PxShape* shape = physics->createShape(boxGeom, *material);
    if (!shape) {
        std::cerr << "Failed to create PxShape for door" << std::endl;
        return;
    }

    // Move shape origin relative to actor
    shape->setLocalPose(PxTransform(PxVec3(halfSize.x, halfSize.y, 0.0f)));

    m_rigidActor->attachShape(*shape);
    shape->release();

    PxRigidBodyExt::updateMassAndInertia(*m_rigidActor, 10.0f);
    m_rigidActor->setAngularDamping(0.1f);
    scene->addActor(*m_rigidActor);

    // Initial model matrix
    m_modelMatrix = glm::translate(glm::mat4(1.0f), m_createInfo.position);
}

void Door::Update(float deltaTime) {
    if (!m_rigidActor) return;

    // Rotate door (test animation)
    const float spinSpeed = glm::radians(100.0f);
    m_rigidActor->setAngularVelocity(PxVec3(0, spinSpeed, 0), true);

    PxTransform pose = m_rigidActor->getGlobalPose();
    glm::vec3 position = { pose.p.x, pose.p.y, pose.p.z };
    glm::quat rotation = { pose.q.w, pose.q.x, pose.q.y, pose.q.z };

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model *= glm::mat4_cast(rotation);

    m_modelMatrix = model;
}

Mesh* Door::GetMesh() const {
    return m_mesh.get();
}



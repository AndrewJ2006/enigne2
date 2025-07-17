#include "PlayerPx.h"
#include "PhysicsManager.h"
#include <iostream> // For std::cerr, std::endl

using namespace physx;

PlayerPhysics::PlayerPhysics()
    : m_controller(nullptr)
    , m_verticalVelocity(0.0f)
    , m_isJumping(false)
    , m_pendingMovement(0.0f)
    , gravity(-9.81f)
{
}

PlayerPhysics::~PlayerPhysics() {
    if (m_controller) {
        m_controller->release();
        m_controller = nullptr;
    }
}

bool PlayerPhysics::Init(const PxVec3& startPosition) {
    PhysicsManager& physicsMgr = PhysicsManager::Get();

    auto* manager = physicsMgr.GetControllerManager();
    auto* material = physicsMgr.GetMaterial();

    if (!manager || !material) {
        std::cerr << "Failed to get controller manager or material from PhysicsManager." << std::endl;
        return false;
    }

    PxCapsuleControllerDesc desc{};
    desc.height = 1.75f;
    desc.radius = 0.4f;
    desc.position = PxExtendedVec3(startPosition.x, startPosition.y, startPosition.z);
    desc.material = material;
    desc.stepOffset = 0.4f;
    desc.slopeLimit = cosf(PxPi / 4.0f);
    desc.contactOffset = 0.15f;
    desc.reportCallback = nullptr;

    m_controller = static_cast<PxCapsuleController*>(manager->createController(desc));
    if (!m_controller) {
        std::cerr << "Failed to create controller." << std::endl;
        return false;
    }

    m_verticalVelocity = 0.0f;
    m_isJumping = false;
    m_pendingMovement = PxVec3(0.0f);

    return true;
}

void PlayerPhysics::Move(const PxVec3& direction) {
    // Accumulate horizontal movement; vertical is handled separately
    m_pendingMovement.x += direction.x;
    m_pendingMovement.z += direction.z;
}

void PlayerPhysics::Jump() {
    // Can only jump if on ground and not already jumping
    if (!m_isJumping && IsOnGround()) {
        m_verticalVelocity = 7.0f;  // Jump impulse strength
        m_isJumping = true;
    }
}

void PlayerPhysics::Update(float deltaTime) {
    if (!m_controller)
        return;

    // Apply gravity when jumping or in air
    if (m_isJumping || !IsOnGround()) {
        m_verticalVelocity += gravity * deltaTime;
    }
    else {
        // On ground and not jumping
        m_verticalVelocity = 0.0f;
    }

    // Compose horizontal movement scaled by speed and deltaTime
    float horizontalSpeed = 5.0f;
    PxVec3 horizontalMove(
        m_pendingMovement.x * horizontalSpeed * deltaTime,
        0.0f,
        m_pendingMovement.z * horizontalSpeed * deltaTime);

    // Vertical movement based on vertical velocity
    PxVec3 verticalMove(0.0f, m_verticalVelocity * deltaTime, 0.0f);

    // Total movement vector
    PxVec3 totalMove = horizontalMove + verticalMove;

    PxControllerFilters filters;
    PxControllerCollisionFlags collisionFlags = m_controller->move(totalMove, 0.001f, deltaTime, filters);

    // Reset horizontal movement accumulator
    m_pendingMovement = PxVec3(0.0f);

    // Check if on ground by testing collision flags
    bool onGround = (static_cast<uint32_t>(collisionFlags) & static_cast<uint32_t>(PxControllerCollisionFlag::eCOLLISION_DOWN)) != 0;

    if (onGround) {
        m_isJumping = false;
        m_verticalVelocity = 0.0f;
    }
}

physx::PxController* PlayerPhysics::GetController() const {
    return m_controller;
}

bool PlayerPhysics::IsOnGround() const {
    if (!m_controller)
        return false;

    PxControllerState state;
    m_controller->getState(state);

    return (static_cast<uint32_t>(state.collisionFlags) & static_cast<uint32_t>(PxControllerCollisionFlag::eCOLLISION_DOWN)) != 0;
}

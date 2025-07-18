#include "Player.h"
#include "ManagerPx.h"

using namespace physx;

Player::Player()
    : m_raycast(PhysicsManager::Get().GetScene())
{
}

Player::~Player() = default;

bool Player::Init(const PxVec3& startPosition) {
    return m_physics.Init(startPosition);
}

void Player::Update(float deltaTime) {
    m_physics.Update(deltaTime);
}

void Player::Move(const PxVec3& direction) {
    m_physics.Move(direction); // ? now correctly calling with one argument
}

void Player::Jump() {
    m_physics.Jump();
}

PxVec3 Player::GetPosition() const {
    if (auto ctrl = m_physics.GetController()) {
        PxExtendedVec3 pos = ctrl->getPosition();
        return PxVec3(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
    }
    return PxVec3(0);
}

PxController* Player::GetController() const {
    return m_physics.GetController();
}

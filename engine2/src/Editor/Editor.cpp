#include "Editor.h"
#include "CameraEditor.h"
#include "Physics.h"
#include "Backend.h"
#include "Utils.h" 
using namespace physx;

void Editor::Update(float deltaTime) {
    if (m_camera) m_camera->Update(deltaTime);

    static bool fPressedLastFrame = false;
    bool fPressed = Backend::IsKeyPressed(GLFW_KEY_F);
    if (fPressed && !fPressedLastFrame) {
        PerformRaycast();
    }
    fPressedLastFrame = fPressed;
}

void Editor::PerformRaycast() {
    if (!m_camera) return;

    PxScene* scene = PhysicsManager::Get().GetScene();

    glm::vec3 camPos = m_camera->GetPosition();
    glm::vec3 camFront = glm::normalize(m_camera->GetFront());

    float maxDistance = 3.5f;

    Door* hitDoor = Util::RaycastForDoor(scene, camPos, camFront, maxDistance);
    if (hitDoor) {
        hitDoor->ToggleOpenClose();
    }
}

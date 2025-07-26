#include "Editor.h"
#include "CameraEditor.h"
#include "Physics.h"
#include "Door.h"
#include "Backend.h"

using namespace physx;
extern std::vector<Door*> g_Doors;

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
    RaycastingPx raycaster(scene);

    glm::vec3 camPos = m_camera->GetPosition();
    glm::vec3 camFront = glm::normalize(m_camera->GetFront());

    PxVec3 origin(camPos.x, camPos.y, camPos.z);
    PxVec3 direction(camFront.x, camFront.y, camFront.z);

    PxRaycastBuffer hitBuffer;
    float maxDistance = 3.5f;

    if (raycaster.Raycast(origin, direction, maxDistance, hitBuffer)) {
        PxActor* hitActor = hitBuffer.block.actor;
        if (hitActor) {
            for (Door* door : g_Doors) {
                if (door && door->GetRigidActor() == hitActor) {
                    door->ToggleOpenClose();
                    break;
                }
            }
        }
    }
}

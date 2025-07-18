#include "World/World.h"
#include "Types/Wall.h"
#include "Types/Plane.h"
#include "Types/Door.h"
#include "Renderer/Renderer.h"
#include "AssetManager/AssetManager.h"
#include "JSON.h"
#include "Shader/Shader.h"
#include "Types/Mesh.h"
#include "ManagerPx.h"
#include "ScenePx.h"

#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

// Declare the external global vector of Door pointers
extern std::vector<Door*> g_Doors;

World::World() {}

World::~World() {}

void World::Init() {
    // Initialize PhysX system first
    PhysicsManager::Get().Init();

    // Create static floor (make static or fix call)
    ScenePx::CreateStaticFloor();

    nlohmann::json json = JSONLoader::LoadFromFile("StartHouse.json");

    // Parse door info first
    std::vector<DoorCreateInfo> doorInfos = JSONLoader::ParseDoors(json);

    // Create Door objects, initialize them, and add to global door vector
    for (auto& doorInfo : doorInfos) {
        auto door = std::make_unique<Door>(doorInfo);
        door->Init();

        // Add raw pointer to global vector for raycast interaction
        g_Doors.push_back(door.get());

        // Store unique_ptr locally to manage lifetime
        m_doors.push_back(std::move(door));
    }

    // Create Wall objects, set door info, then initialize
    std::vector<WallCreateInfo> wallInfos = JSONLoader::ParseWalls(json);
    for (const auto& wallInfo : wallInfos) {
        auto wall = std::make_unique<Wall>(wallInfo);
        wall->SetDoors(doorInfos);
        wall->Init();
        m_walls.push_back(std::move(wall));
    }

    // Create Plane objects and initialize
    std::vector<PlaneCreateInfo> planeInfos = JSONLoader::ParsePlanes(json);
    for (const auto& planeInfo : planeInfos) {
        auto plane = std::make_unique<Plane>(planeInfo);
        plane->Init();
        m_planes.push_back(std::move(plane));
    }

    std::cout << "World initialized from JSON\n";
}

void World::Update(float deltaTime) {
    // Step PhysX simulation
    PhysicsManager::Get().Step(deltaTime);

    for (auto& wall : m_walls) wall->Update();
    for (auto& plane : m_planes) plane->Update();
    for (auto& door : m_doors) door->Update(deltaTime);
}

void World::Draw() {
    auto* shader = Renderer::GetShader();
    if (!shader) return;

    shader->Use();

    // Draw walls (light gray)
    for (const auto& wall : m_walls) {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.7f, 0.7f, 0.7f));
        if (wall->GetMesh()) wall->GetMesh()->Draw();
    }

    // Draw planes (darker gray)
    for (const auto& plane : m_planes) {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.4f, 0.4f, 0.4f));
        if (plane->GetMesh()) plane->GetMesh()->Draw();
    }

    // Draw doors (brownish color)
    for (const auto& door : m_doors) {
        glm::mat4 model = door->GetModelMatrix();
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.55f, 0.27f, 0.07f));
        if (door->GetMesh()) door->GetMesh()->Draw();
    }
}

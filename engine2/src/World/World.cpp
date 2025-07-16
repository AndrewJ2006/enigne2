#include "World/World.h"
#include "Types/Wall.h"
#include "Types/Plane.h"
#include "Types/Door.h"
#include "Renderer/Renderer.h"
#include "AssetManager/AssetManager.h"
#include "JSON.h"
#include "Shader/Shader.h"
#include "Types/Mesh.h"
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

World::World() {}

World::~World() {}

void World::Init() {
    nlohmann::json json = JSONLoader::LoadFromFile("StartHouse.json");

    // Parse door info first
    std::vector<DoorCreateInfo> doorInfos = JSONLoader::ParseDoors(json);

    // Create Door objects and initialize them
    for (auto& doorInfo : doorInfos) {
        // Make sure DoorCreateInfo has 'size' populated from JSON "Size"
        auto door = std::make_unique<Door>(doorInfo);
        door->Init();
        m_doors.push_back(std::move(door));
    }

    // Create Wall objects, set door info, then initialize
    std::vector<WallCreateInfo> wallInfos = JSONLoader::ParseWalls(json);
    for (const auto& wallInfo : wallInfos) {
        auto wall = std::make_unique<Wall>(wallInfo);
        wall->SetDoors(doorInfos);  // Pass door info for door cutting (optional)
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
    for (auto& wall : m_walls) wall->Update();
    for (auto& plane : m_planes) plane->Update();
    for (auto& door : m_doors) door->Update();
}

void World::Draw() {
    auto* shader = Renderer::GetShader();
    if (!shader) return;

    shader->Use();

    // Draw walls (light gray)
    for (const auto& wall : m_walls) {
        glm::mat4 model = glm::mat4(1.0f); // Walls are defined in world space already
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.7f, 0.7f, 0.7f)); // Light gray walls
        if (wall->GetMesh()) wall->GetMesh()->Draw();
    }

    // Draw planes (darker gray)
    for (const auto& plane : m_planes) {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.4f, 0.4f, 0.4f)); // Dark gray planes
        if (plane->GetMesh()) plane->GetMesh()->Draw();
    }

    // Draw doors (brownish color)
    // Door meshes are already transformed by position/rotation inside Door::Init(),
    // so we can draw them with identity model matrix here.
    for (const auto& door : m_doors) {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.55f, 0.27f, 0.07f)); // Brown door color
        if (door->GetMesh()) door->GetMesh()->Draw();
    }
}

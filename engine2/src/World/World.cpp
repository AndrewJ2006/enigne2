#include "World/World.h"
#include "Types/Wall.h"
#include "Types/Plane.h"
#include "Types/Door.h"
#include "Renderer/Renderer.h"
#include "AssetManager/AssetManager.h"
#include "JSON.h"
#include "Shader/Shader.h"
#include "Types/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

World::World() {}

World::~World() {}

void World::Init() {
    nlohmann::json json = JSONLoader::LoadFromFile("StartHouse.json");

    for (auto& info : JSONLoader::ParseWalls(json)) {
        auto wall = std::make_unique<Wall>(info);
        wall->Init();
        m_walls.push_back(std::move(wall));
    }

    for (auto& info : JSONLoader::ParsePlanes(json)) {
        auto plane = std::make_unique<Plane>(info);
        plane->Init();
        m_planes.push_back(std::move(plane));
    }

    for (auto& info : JSONLoader::ParseDoors(json)) {
        auto door = std::make_unique<Door>(info);
        door->Init();
        m_doors.push_back(std::move(door));
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

    // Draw walls (gray)
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
    for (const auto& door : m_doors) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), door->GetPosition());
        // TODO: apply rotation if needed
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.55f, 0.27f, 0.07f)); // Brown door color
        if (door->GetMesh()) door->GetMesh()->Draw();
    }
}

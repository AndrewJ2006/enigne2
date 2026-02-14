#define GLM_ENABLE_EXPERIMENTAL

#include "World/World.h"
#include "Types/Wall.h"
#include "Types/Plane.h"
#include "Types/Door.h"
#include "Renderer/Renderer.h"
#include "AssetManager/AssetManager.h"
#include "JSON.h"
#include "Shader/Shader.h"
#include "Types/Mesh.h"
#include "Physics.h"
#include "TerrainGen.h"
#include "Model.h"

#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm> 


extern std::vector<Door*> g_Doors;

World::World()
    : m_terrain(100, 100, 0.05f, 5.0f) 
{
}

World::~World() {}

void World::Init() {
    
    PhysicsManager::Get().Init();

   
    ScenePx scene;
    scene.CreateStaticFloor();

    
    m_terrain.Generate();

   
    nlohmann::json json = JSONLoader::LoadFromFile("StartHouse.json");

   
    std::vector<DoorCreateInfo> doorInfos = JSONLoader::ParseDoors(json);

   
    for (auto& doorInfo : doorInfos) {
        auto door = std::make_unique<Door>(doorInfo);
        door->Init();

        
        if (std::find(g_Doors.begin(), g_Doors.end(), door.get()) == g_Doors.end()) {
            g_Doors.push_back(door.get());
        }

       
        m_doors.push_back(std::move(door));
    }

   
    std::vector<WallCreateInfo> wallInfos = JSONLoader::ParseWalls(json);
    for (const auto& wallInfo : wallInfos) {
        auto wall = std::make_unique<Wall>(wallInfo);
        wall->SetDoors(doorInfos);
        wall->Init();
        m_walls.push_back(std::move(wall));
    }

  
    std::vector<PlaneCreateInfo> planeInfos = JSONLoader::ParsePlanes(json);
    for (const auto& planeInfo : planeInfos) {
        auto plane = std::make_unique<Plane>(planeInfo);
        plane->Init();
        m_planes.push_back(std::move(plane));
    }

    // Load models from JSON
    std::vector<ModelCreateInfo> modelInfos = JSONLoader::ParseModels(json);
    for (const auto& modelInfo : modelInfos) {
        WorldModel wm;
        wm.model = AssetManager::LoadModel(modelInfo.path);
        
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, modelInfo.position);
        transform = glm::rotate(transform, glm::radians(modelInfo.rotation.x), glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, glm::radians(modelInfo.rotation.y), glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, glm::radians(modelInfo.rotation.z), glm::vec3(0, 0, 1));
        transform = glm::scale(transform, modelInfo.scale);
        wm.transform = transform;

        m_models.push_back(std::move(wm));
    }

    std::cout << "World initialized from JSON\n";
    std::cout << "Models loaded: " << m_models.size() << "\n";
}

void World::Update(float deltaTime) {
   
    PhysicsManager::Get().Step(deltaTime);

   
    for (auto& wall : m_walls) wall->Update();
    for (auto& plane : m_planes) plane->Update();

   
    for (auto& door : m_doors) door->Update(deltaTime);
}

void World::Draw() {
    auto* shader = Renderer::GetShader();
    if (!shader) return;

    shader->Use();

    
    for (const auto& wall : m_walls) {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.7f, 0.7f, 0.7f));
        if (wall->GetMesh()) wall->GetMesh()->Draw();
    }

    
    for (const auto& plane : m_planes) {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.4f, 0.4f, 0.4f));
        if (plane->GetMesh()) plane->GetMesh()->Draw();
    }

    
    for (const auto& door : m_doors) {
        glm::mat4 model = door->GetModelMatrix();
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.55f, 0.27f, 0.07f));
        if (door->GetMesh()) door->GetMesh()->Draw();
    }

    // Draw terrain
    {
        glm::mat4 model = glm::mat4(1.0f);
        shader->SetMat4("model", model);
        shader->SetBool("useTexture", false);
        shader->SetVec3("uColor", glm::vec3(0.2f, 0.6f, 0.2f));
        if (m_terrain.GetMesh()) m_terrain.GetMesh()->Draw();
    }

    // Draw loaded models
    for (const auto& wm : m_models) {
        if (wm.model) {
            shader->SetMat4("model", wm.transform);
            wm.model->Draw(*shader);
        }
    }
}

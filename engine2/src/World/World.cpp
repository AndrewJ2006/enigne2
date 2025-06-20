#include "World/World.h"
#include "Types/Mesh.h"
#include "AssetManager/AssetManager.h"
#include "Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

World::World() {}

World::~World() {}

void World::Init() {
    m_cubeMesh = std::make_unique<Mesh>(
        AssetManager::GetCubeVertices(),
        AssetManager::GetCubeIndices()
    );

    m_cubePositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_cubePositions.push_back(glm::vec3(2.0f, 0.0f, 0.0f));

    std::cout << "World initialized with cube mesh and positions\n";
}

void World::Update(float deltaTime) {
    // Your update logic (if any)
}

void World::Draw() {
    if (!m_cubeMesh) return;

    Shader* shader = Renderer::GetShader();
    if (!shader) return;

    for (const auto& pos : m_cubePositions) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);

        shader->Use();
        shader->SetMat4("model", model);

        m_cubeMesh->Draw();
    }
}

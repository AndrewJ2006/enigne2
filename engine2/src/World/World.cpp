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

    // Clear any existing positions just in case
    m_cubePositions.clear();

    // Example: Create a 10x10x10 grid of cubes spaced by 2 units
    int gridSize = 20;
    float spacing = 10.0f;

    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            for (int z = 0; z < gridSize; ++z) {
                glm::vec3 pos(
                    x * spacing,
                    y * spacing,
                    z * spacing
                );
                m_cubePositions.push_back(pos);
            }
        }
    }
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

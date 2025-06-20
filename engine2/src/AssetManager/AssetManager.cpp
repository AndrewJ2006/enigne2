#include "AssetManager.h"
#include "Base/PrimitiveShapes.h"  // contains Primitves namespace
#include "Base/Types.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>  // for glm::normalize

std::vector<Vertex> AssetManager::s_cubeVertices;
std::vector<unsigned int> AssetManager::s_cubeIndices;

void AssetManager::Init() {
    auto positions = Primitives::CreateCubeVertices(0.5f);  // note namespace spelling exactly as in PrimitiveShapes.h
    auto indices = Primitives::CreateCubeIndices();

    s_cubeVertices.clear();
    for (const auto& pos : positions) {
        glm::vec3 normal = glm::normalize(pos);  // approximate normal vector
        glm::vec2 texCoords(0.0f, 0.0f);         // placeholder UV coords
        s_cubeVertices.emplace_back(pos, normal, texCoords);
    }

    s_cubeIndices = indices;
}

const std::vector<Vertex>& AssetManager::GetCubeVertices() {
    return s_cubeVertices;
}

const std::vector<unsigned int>& AssetManager::GetCubeIndices() {
    return s_cubeIndices;
}

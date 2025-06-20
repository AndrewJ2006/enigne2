#include "AssetManager.h"
#include "Base/PrimitiveShapes.h" 
#include "Vertex.h"

static std::vector<Vertex> s_cubeVertices;
static std::vector<unsigned int> s_cubeIndices;

void AssetManager::Init() {
    auto positions = Primitves::CreateCubeVertices(0.5f);
    auto indices = Primitves::CreateCubeIndices();

    s_cubeVertices.clear();
    for (const auto& pos : positions) {
        Vertex v;
        v.position = pos;
        v.normal = glm::vec3(0.0f, 1.0f, 0.0f);  // default normal
        v.texCoords = glm::vec2(0.0f);           // default texCoords
        s_cubeVertices.push_back(v);
    }

    s_cubeIndices = indices;
}

const std::vector<Vertex>& AssetManager::GetCubeVertices() {
    return s_cubeVertices;
}

const std::vector<unsigned int>& AssetManager::GetCubeIndices() {
    return s_cubeIndices;
}

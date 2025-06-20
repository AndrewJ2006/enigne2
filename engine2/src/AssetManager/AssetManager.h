#pragma once
#include <vector>
#include "Vertex.h"

namespace AssetManager {
    void Init();
    const std::vector<Vertex>& GetCubeVertices();
    const std::vector<unsigned int>& GetCubeIndices();
    const std::vector<Vertex>& GetPlaneVertices();
    const std::vector<unsigned int>& GetPlaneIndices();
}

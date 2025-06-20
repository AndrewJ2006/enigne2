#pragma once
#include <vector>
#include "Base/Types.h"  // for Vertex

class AssetManager {
public:
    static void Init();
    static const std::vector<Vertex>& GetCubeVertices();
    static const std::vector<unsigned int>& GetCubeIndices();

private:
    static std::vector<Vertex> s_cubeVertices;
    static std::vector<unsigned int> s_cubeIndices;
};

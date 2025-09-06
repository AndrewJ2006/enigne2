#pragma once
#include <vector>
#include "Base/Types.h"  // For Vertex or other asset types

class AssetManager {
public:
    static void Init();

    // Add other asset getters here as you add assets, for example:
    // static const std::vector<Vertex>& GetSomeModelVertices();

private:
    // Add private static members here as needed for assets.
};

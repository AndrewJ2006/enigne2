#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"

namespace Util {

    // Generates a cube mesh centered at the origin with size 1
    void CreateCubeMesh(
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        const glm::vec3& color = glm::vec3(1.0f)
    );

    // Generates a flat quad/plane mesh from 4 corner points
    void CreatePlaneMesh(
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        const glm::vec3& p0,
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& p3
    );

    // Generates a prism-shaped wall from a sequence of base points
    void CreatePrismWallMesh(
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        const std::vector<glm::vec3>& points,
        float height,
        float thickness = 0.2f
    );

} // namespace Util

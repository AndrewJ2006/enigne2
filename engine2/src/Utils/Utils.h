#pragma once

// Standard library
#include <vector>

// GLM
#include <glm/glm.hpp>

// Project-specific includes
#include "Mesh.h"
#include "Transform.h"  // Needed for cube transforms

namespace Util {

    // Result structure for raycasting against cubes
    struct CubeRayResult {
        bool hitFound = false;
        float distanceToHit = 0.0f;
        glm::vec3 hitPosition = glm::vec3(0.0f);
        glm::vec3 hitNormal = glm::vec3(0.0f);
        Transform cubeTransform; // Transform of the cube hit
    };

    // Mesh Generation Utilities

    void CreateCubeMesh(
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        const glm::vec3& color = glm::vec3(1.0f)
    );

    void CreatePlaneMesh(
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        const glm::vec3& p0,
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& p3
    );

    void CreatePrismWallMesh(
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        const std::vector<glm::vec3>& points,
        float height,
        float thickness = 0.2f
    );

    // Raycasting

    [[nodiscard]] CubeRayResult CastCubeRay(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDir,
        const std::vector<Transform>& cubeTransforms,
        float maxDistance
    );

    [[nodiscard]] bool RayIntersectsTriangle(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDir,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        float& t
    );

    [[nodiscard]] glm::vec3 GetMouseRayDir(
        const glm::mat4& projection,
        const glm::mat4& view,
        int windowWidth,
        int windowHeight,
        int mouseX,
        int mouseY
    );

} // namespace Util

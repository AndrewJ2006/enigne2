#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

namespace Hardcoded {
    inline glm::vec3 planeBottomLeft = glm::vec3(-0.5f, 0.0f, -0.5f);
    inline glm::vec3 planeBottomRight = glm::vec3(0.5f, 0.0f, -0.5f);
    inline glm::vec3 planeTopRight = glm::vec3(0.5f, 0.0f, 0.5f);
    inline glm::vec3 planeTopLeft = glm::vec3(-0.5f, 0.0f, 0.5f);
    inline glm::vec3 planeNormal = glm::vec3(0.0f, 1.0f, 0.0f);

    inline std::vector<Vertex> GetPlaneVertices() {
        return {
            Vertex(planeBottomLeft, planeNormal, glm::vec2(0.0f, 0.0f)),
            Vertex(planeBottomRight, planeNormal, glm::vec2(1.0f, 0.0f)),
            Vertex(planeTopRight, planeNormal, glm::vec2(1.0f, 1.0f)),
            Vertex(planeTopLeft, planeNormal, glm::vec2(0.0f, 1.0f))
        };
    }

    inline std::vector<unsigned int> GetPlaneIndices() {
        return { 0, 1, 2, 2, 3, 0 };
    }
}

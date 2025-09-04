#include "Utils.h"
#include <glm/glm.hpp>

namespace Util {

    void CreateCubeMesh(std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices, const glm::vec3& color) {
        glm::vec3 half(0.5f);

        glm::vec3 p[8] = {
            {-half.x, -half.y,  half.z}, { half.x, -half.y,  half.z},
            { half.x,  half.y,  half.z}, {-half.x,  half.y,  half.z},
            {-half.x, -half.y, -half.z}, { half.x, -half.y, -half.z},
            { half.x,  half.y, -half.z}, {-half.x,  half.y, -half.z}
        };

        outVertices = {
            {p[0], {0,0,1}, {0,0}}, {p[1], {0,0,1}, {1,0}}, {p[2], {0,0,1}, {1,1}}, {p[3], {0,0,1}, {0,1}},
            {p[5], {0,0,-1}, {0,0}}, {p[4], {0,0,-1}, {1,0}}, {p[7], {0,0,-1}, {1,1}}, {p[6], {0,0,-1}, {0,1}},
            {p[4], {-1,0,0}, {0,0}}, {p[0], {-1,0,0}, {1,0}}, {p[3], {-1,0,0}, {1,1}}, {p[7], {-1,0,0}, {0,1}},
            {p[1], {1,0,0}, {0,0}}, {p[5], {1,0,0}, {1,0}}, {p[6], {1,0,0}, {1,1}}, {p[2], {1,0,0}, {0,1}},
            {p[3], {0,1,0}, {0,0}}, {p[2], {0,1,0}, {1,0}}, {p[6], {0,1,0}, {1,1}}, {p[7], {0,1,0}, {0,1}},
            {p[4], {0,-1,0}, {0,0}}, {p[5], {0,-1,0}, {1,0}}, {p[1], {0,-1,0}, {1,1}}, {p[0], {0,-1,0}, {0,1}}
        };

        outIndices = {
            0,1,2, 0,2,3,   4,5,6, 4,6,7,  8,9,10, 8,10,11,
            12,13,14,12,14,15, 16,17,18,16,18,19, 20,21,22,20,22,23
        };
    }

    void CreatePlaneMesh(std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) {
        glm::vec3 normal(0, 1, 0);
        outVertices = {
            {p0, normal, {0,0}}, {p1, normal, {1,0}}, {p2, normal, {1,1}}, {p3, normal, {0,1}},
            {p0, -normal, {0,0}}, {p3, -normal, {1,0}}, {p2, -normal, {1,1}}, {p1, -normal, {0,1}},
        };

        outIndices = {
            0,1,2, 2,3,0,
            4,5,6, 6,7,4
        };
    }

    void CreatePrismWallMesh(std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices, const std::vector<glm::vec3>& points, float height, float thickness) {
        unsigned int indexOffset = 0;

        for (size_t i = 0; i + 1 < points.size(); ++i) {
            glm::vec3 p0 = points[i];
            glm::vec3 p1 = points[i + 1];
            glm::vec3 dir = glm::normalize(p1 - p0);
            glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(0, 1, 0), dir));
            glm::vec3 offset = normal * (thickness * 0.5f);

            glm::vec3 bottom0 = p0 - offset;
            glm::vec3 bottom1 = p1 - offset;
            glm::vec3 top0 = bottom0 + glm::vec3(0, height, 0);
            glm::vec3 top1 = bottom1 + glm::vec3(0, height, 0);

            glm::vec3 b0r = p0 + offset;
            glm::vec3 b1r = p1 + offset;
            glm::vec3 t0r = b0r + glm::vec3(0, height, 0);
            glm::vec3 t1r = b1r + glm::vec3(0, height, 0);

            std::vector<Vertex> verts = {
                {bottom0, normal, {0,0}}, {bottom1, normal, {1,0}}, {top1, normal, {1,1}}, {top0, normal, {0,1}},
                {b1r, -normal, {0,0}}, {b0r, -normal, {1,0}}, {t0r, -normal, {1,1}}, {t1r, -normal, {0,1}},
                {b0r, {-1,0,0}, {0,0}}, {bottom0, {-1,0,0}, {1,0}}, {top0, {-1,0,0}, {1,1}}, {t0r, {-1,0,0}, {0,1}},
                {bottom1, {1,0,0}, {0,0}}, {b1r, {1,0,0}, {1,0}}, {t1r, {1,0,0}, {1,1}}, {top1, {1,0,0}, {0,1}},
                {top0, {0,1,0}, {0,0}}, {top1, {0,1,0}, {1,0}}, {t1r, {0,1,0}, {1,1}}, {t0r, {0,1,0}, {0,1}},
                {b0r, {0,-1,0}, {0,0}}, {b1r, {0,-1,0}, {1,0}}, {bottom1, {0,-1,0}, {1,1}}, {bottom0, {0,-1,0}, {0,1}}
            };

            for (int face = 0; face < 6; ++face) {
                unsigned int base = indexOffset + face * 4;
                outIndices.insert(outIndices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
            }

            outVertices.insert(outVertices.end(), verts.begin(), verts.end());
            indexOffset += 24;
        }
    }

} 

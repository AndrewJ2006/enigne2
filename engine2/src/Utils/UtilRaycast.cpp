#include "Utils.h"
#include <glm/glm.hpp>

namespace Util {

    CubeRayResult CastCubeRay(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDir,
        const std::vector<Transform>& cubeTransforms,
        float maxDistance
    ) {
        CubeRayResult closestHit;

        for (const auto& transform : cubeTransforms) {
            std::vector<Vertex> verts;
            std::vector<unsigned int> indices;
            CreateCubeMesh(verts, indices);  // Call Util::CreateCubeMesh (same namespace)

            glm::mat4 model = transform.to_mat4();

            for (size_t i = 0; i < indices.size(); i += 3) {
                glm::vec3 v0 = glm::vec3(model * glm::vec4(verts[indices[i]].position, 1.0f));
                glm::vec3 v1 = glm::vec3(model * glm::vec4(verts[indices[i + 1]].position, 1.0f));
                glm::vec3 v2 = glm::vec3(model * glm::vec4(verts[indices[i + 2]].position, 1.0f));

                float t;
                if (RayIntersectsTriangle(rayOrigin, rayDir, v0, v1, v2, t) && t < maxDistance) {
                    if (!closestHit.hitFound || t < closestHit.distanceToHit) {
                        closestHit.hitFound = true;
                        closestHit.distanceToHit = t;
                        closestHit.hitPosition = rayOrigin + rayDir * t;
                        closestHit.hitNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
                        closestHit.cubeTransform = transform;
                    }
                }
            }
        }

        return closestHit;
    }

    bool RayIntersectsTriangle(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDir,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        float& t
    ) {
        const float EPSILON = 1e-6f;
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 h = glm::cross(rayDir, edge2);
        float a = glm::dot(edge1, h);

        if (std::abs(a) < EPSILON)
            return false;

        float f = 1.0f / a;
        glm::vec3 s = rayOrigin - v0;
        float u = f * glm::dot(s, h);
        if (u < 0.0f || u > 1.0f)
            return false;

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(rayDir, q);
        if (v < 0.0f || u + v > 1.0f)
            return false;

        t = f * glm::dot(edge2, q);
        return t > EPSILON;
    }

    glm::vec3 GetMouseRayDir(
        const glm::mat4& projection,
        const glm::mat4& view,
        int windowWidth,
        int windowHeight,
        int mouseX,
        int mouseY
    ) {
        float x = (2.0f * mouseX) / windowWidth - 1.0f;
        float y = 1.0f - (2.0f * mouseY) / windowHeight;
        glm::vec4 rayClip(x, y, -1.0f, 1.0f);
        glm::vec4 rayEye = glm::inverse(projection) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        glm::vec4 rayWorld = glm::inverse(view) * rayEye;
        return glm::normalize(glm::vec3(rayWorld));
    }

} // namespace Util

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Door.h"
#include <PxPhysicsAPI.h>

namespace Util {

   

    
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

    
    Door* RaycastForDoor(
        physx::PxScene* scene,
        const glm::vec3& origin,
        const glm::vec3& direction,
        float maxDistance
    );

} 

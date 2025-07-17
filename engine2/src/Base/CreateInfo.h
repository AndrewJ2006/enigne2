#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct WallCreateInfo {
    std::vector<glm::vec3> points;
    float height;
    std::string material;
    float textureOffsetU = 0.0f;
    float textureOffsetV = 0.0f;
    float textureRotation = 0.0f;
    float textureScale = 1.0f;
    bool useReversePointOrder = false;
    std::string wallType;
};

struct PlaneCreateInfo {
    glm::vec3 p0, p1, p2, p3;
    std::string material;
    float textureOffsetU = 0.0f;
    float textureOffsetV = 0.0f;
    float textureRotation = 0.0f;
    float textureScale = 1.0f;
};

struct DoorCreateInfo {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 size = glm::vec3(1.0f, 2.0f, 0.1f);
    glm::vec3 playerPosition = glm::vec3(0.0f);
    glm::vec3 playerForward = glm::vec3(0.0f, 0.0f, -1.0f);
    float mass = 10.0f;
};

#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

// Structs for wall, plane, door

struct WallCreateInfo {
    float height;
    std::string material;
    std::vector<glm::vec3> points;
    float textureOffsetU;
    float textureOffsetV;
    float textureRotation;
    float textureScale;
    bool useReversePointOrder;
    std::string wallType;
};

struct PlaneCreateInfo {
    std::string material;
    glm::vec3 p0, p1, p2, p3;
    float textureOffsetU;
    float textureOffsetV;
    float textureRotation;
    float textureScale;
};

struct DoorCreateInfo {
    glm::vec3 position;
    glm::vec3 rotation;
};

class JSONLoader {
public:
    static nlohmann::json LoadFromFile(const std::string& filename);

    static std::vector<WallCreateInfo> ParseWalls(const nlohmann::json& json);
    static std::vector<PlaneCreateInfo> ParsePlanes(const nlohmann::json& json);
    static std::vector<DoorCreateInfo> ParseDoors(const nlohmann::json& json);
};

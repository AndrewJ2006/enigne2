#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "CreateInfo.h"

class JSONLoader {
public:
    static nlohmann::json LoadFromFile(const std::string& filename);

    static std::vector<WallCreateInfo> ParseWalls(const nlohmann::json& json);
    static std::vector<PlaneCreateInfo> ParsePlanes(const nlohmann::json& json);
    static std::vector<DoorCreateInfo> ParseDoors(const nlohmann::json& json);
};

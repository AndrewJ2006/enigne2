#include "JSON.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>

nlohmann::json JSONLoader::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open JSON file: " << filename << "\n";
        return nlohmann::json{};
    }
    nlohmann::json data;
    file >> data;
    return data;
}

std::vector<WallCreateInfo> JSONLoader::ParseWalls(const nlohmann::json& json) {
    std::vector<WallCreateInfo> walls;
    if (!json.contains("Walls")) return walls;

    for (const auto& w : json["Walls"]) {
        WallCreateInfo wall;
        wall.height = w.value("Height", 0.0f);
        wall.material = w.value("Material", "");
        wall.textureOffsetU = w.value("TextureOffsetU", 0.0f);
        wall.textureOffsetV = w.value("TextureOffsetV", 0.0f);
        wall.textureRotation = w.value("TextureRotation", 0.0f);
        wall.textureScale = w.value("TextureScale", 1.0f);
        wall.useReversePointOrder = w.value("UseReversePointOrder", false);
        wall.wallType = w.value("WallType", "");

        if (w.contains("Points")) {
            for (const auto& pt : w["Points"]) {
                if (pt.is_array() && pt.size() == 3) {
                    wall.points.emplace_back(pt[0].get<float>(), pt[1].get<float>(), pt[2].get<float>());
                }
            }
        }

        if (wall.useReversePointOrder) {
            std::reverse(wall.points.begin(), wall.points.end());
        }

        walls.push_back(wall);
    }

    return walls;
}

std::vector<PlaneCreateInfo> JSONLoader::ParsePlanes(const nlohmann::json& json) {
    std::vector<PlaneCreateInfo> planes;
    if (!json.contains("Planes")) return planes;

    for (const auto& p : json["Planes"]) {
        PlaneCreateInfo plane;
        plane.material = p.value("Material", "");
        plane.p0 = glm::vec3(p["P0"][0], p["P0"][1], p["P0"][2]);
        plane.p1 = glm::vec3(p["P1"][0], p["P1"][1], p["P1"][2]);
        plane.p2 = glm::vec3(p["P2"][0], p["P2"][1], p["P2"][2]);
        plane.p3 = glm::vec3(p["P3"][0], p["P3"][1], p["P3"][2]);
        plane.textureOffsetU = p.value("TextureOffsetU", 0.0f);
        plane.textureOffsetV = p.value("TextureOffsetV", 0.0f);
        plane.textureRotation = p.value("TextureRotation", 0.0f);
        plane.textureScale = p.value("TextureScale", 1.0f);

        planes.push_back(plane);
    }

    return planes;
}

std::vector<DoorCreateInfo> JSONLoader::ParseDoors(const nlohmann::json& json) {
    std::vector<DoorCreateInfo> doors;
    if (!json.contains("Doors")) return doors;

    for (const auto& d : json["Doors"]) {
        DoorCreateInfo door;
        door.position = glm::vec3(d["Position"][0], d["Position"][1], d["Position"][2]);
        door.rotation = glm::vec3(d["Rotation"][0], d["Rotation"][1], d["Rotation"][2]);

        if (d.contains("Size") && d["Size"].is_array() && d["Size"].size() == 3) {
            door.size = glm::vec3(d["Size"][0], d["Size"][1], d["Size"][2]);
        }
        else {
            door.size = glm::vec3(1.0f, 2.0f, 0.1f); 
        }

        doors.push_back(door);
    }

    return doors;
}

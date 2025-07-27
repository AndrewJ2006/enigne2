#pragma once

#include <vector>
#include <memory>
#include "TerrainGen.h"

class Wall;
class Plane;
class Door;

class World {
public:
    World();
    ~World();

    void Init();
    void Update(float deltaTime);
    void Draw();

private:
    std::vector<std::unique_ptr<Wall>> m_walls;
    std::vector<std::unique_ptr<Plane>> m_planes;
    std::vector<std::unique_ptr<Door>> m_doors;

    TerrainGenerator m_terrain;
};

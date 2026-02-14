#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "TerrainGen.h"

class Wall;
class Plane;
class Door;
class Model;
class Shader;

struct WorldModel {
    std::shared_ptr<Model> model;
    glm::mat4 transform = glm::mat4(1.0f);
};

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
    std::vector<WorldModel> m_models;

    TerrainGenerator m_terrain;
};

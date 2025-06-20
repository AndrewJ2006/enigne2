#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

class Mesh;

class World {
public:
    World();
    ~World();

    void Init();
    void Update(float deltaTime);
    void Draw();

private:
    std::unique_ptr<Mesh> m_cubeMesh;
    std::vector<glm::vec3> m_cubePositions;
};

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Base/PrimitiveShapes.h"
#include "Base/Types.h"

class Cube {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;

    glm::vec3 position;
    glm::vec3 rotation;  
    glm::vec3 scale;

    Cube(float size = 1.0f);

    void setupMesh();
    void render() const;
    glm::mat4 getModelMatrix() const;
};

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;

private:
    void SetupMesh();

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    unsigned int m_VAO, m_VBO, m_EBO;
};

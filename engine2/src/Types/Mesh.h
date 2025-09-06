#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Types.h"

class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Create(const glm::vec3& size, const glm::vec3& color);
    void SetupMesh();

    void Draw() const;

    void SetModelMatrix(const glm::mat4& model) { m_modelMatrix = model; }
    glm::mat4 GetModelMatrix() const { return m_modelMatrix; }

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;

    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
};

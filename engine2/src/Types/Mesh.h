#pragma once
#include <vector>
#include "Types.h"
#include <glad/glad.h>

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    void Draw() const;

    // Added getters to provide access to vertices and indices
    const std::vector<Vertex>& GetVertices() const { return m_vertices; }
    const std::vector<unsigned int>& GetIndices() const { return m_indices; }

private:
    void SetupMesh();

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    unsigned int m_VAO, m_VBO, m_EBO;
};

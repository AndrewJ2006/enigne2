#include "Mesh.h"
#include <glad/glad.h>
#include <iostream>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
    : m_vertices(vertices), m_indices(indices), m_textures(textures) {
    SetupMesh();
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_vertices(std::move(other.m_vertices)),
      m_indices(std::move(other.m_indices)),
      m_textures(std::move(other.m_textures)),
      m_VAO(other.m_VAO), m_VBO(other.m_VBO), m_EBO(other.m_EBO),
      m_modelMatrix(other.m_modelMatrix)
{
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_EBO = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        // Clean up existing resources
        if (m_VAO) {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
        }
        m_vertices = std::move(other.m_vertices);
        m_indices = std::move(other.m_indices);
        m_textures = std::move(other.m_textures);
        m_VAO = other.m_VAO;
        m_VBO = other.m_VBO;
        m_EBO = other.m_EBO;
        m_modelMatrix = other.m_modelMatrix;
        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_EBO = 0;
    }
    return *this;
}

Mesh::~Mesh() {
    if (m_VAO) {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }
}

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw() const {
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader) const {
    // Set useTexture based on whether this mesh actually has valid textures
    bool hasTextures = false;
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i < m_textures.size(); i++) {
        if (m_textures[i].id == 0) continue; // skip invalid textures
        hasTextures = true;
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = m_textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.SetInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    shader.SetBool("useTexture", hasTextures);
    if (!hasTextures) {
        shader.SetVec3("uColor", glm::vec3(0.5f, 0.5f, 0.5f)); // grey fallback
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::Create(const glm::vec3& /*size*/, const glm::vec3& color) {
    glm::vec3 half(0.5f, 0.5f, 0.5f);  // fixed half-size of 1 unit cube

    glm::vec3 positions[8] = {
        {-half.x, -half.y,  half.z},
        { half.x, -half.y,  half.z},
        { half.x,  half.y,  half.z},
        {-half.x,  half.y,  half.z},
        {-half.x, -half.y, -half.z},
        { half.x, -half.y, -half.z},
        { half.x,  half.y, -half.z},
        {-half.x,  half.y, -half.z}
    };

    m_vertices = {
        // Front face
        {positions[0], {0,0,1}, {0,0}}, {positions[1], {0,0,1}, {1,0}},
        {positions[2], {0,0,1}, {1,1}}, {positions[3], {0,0,1}, {0,1}},
        // Back face
        {positions[5], {0,0,-1}, {0,0}}, {positions[4], {0,0,-1}, {1,0}},
        {positions[7], {0,0,-1}, {1,1}}, {positions[6], {0,0,-1}, {0,1}},
        // Left face
        {positions[4], {-1,0,0}, {0,0}}, {positions[0], {-1,0,0}, {1,0}},
        {positions[3], {-1,0,0}, {1,1}}, {positions[7], {-1,0,0}, {0,1}},
        // Right face
        {positions[1], {1,0,0}, {0,0}}, {positions[5], {1,0,0}, {1,0}},
        {positions[6], {1,0,0}, {1,1}}, {positions[2], {1,0,0}, {0,1}},
        // Top face
        {positions[3], {0,1,0}, {0,0}}, {positions[2], {0,1,0}, {1,0}},
        {positions[6], {0,1,0}, {1,1}}, {positions[7], {0,1,0}, {0,1}},
        // Bottom face
        {positions[4], {0,-1,0}, {0,0}}, {positions[5], {0,-1,0}, {1,0}},
        {positions[1], {0,-1,0}, {1,1}}, {positions[0], {0,-1,0}, {0,1}}
    };

    m_indices = {
        0, 1, 2, 0, 2, 3,       // front
        4, 5, 6, 4, 6, 7,       // back
        8, 9,10, 8,10,11,       // left
        12,13,14,12,14,15,      // right
        16,17,18,16,18,19,      // top
        20,21,22,20,22,23       // bottom
    };

    SetupMesh();
}


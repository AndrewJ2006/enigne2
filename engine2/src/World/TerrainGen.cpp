#define GLM_ENABLE_EXPERIMENTAL

#include "TerrainGen.h"
#include <FastNoise/FastNoise.h>
#include <Types/Mesh.h>
#include <vector>

TerrainGenerator::TerrainGenerator(int width, int depth, float scale, float heightMultiplier)
    : m_width(width), m_depth(depth), m_scale(scale), m_heightMultiplier(heightMultiplier)
{
}

void TerrainGenerator::Generate()
{
    FastNoise::SmartNode<> noise = FastNoise::New<FastNoise::Perlin>();
    m_heightMap.resize(m_width * m_depth);

    noise->GenUniformGrid2D(
        m_heightMap.data(),
        0, 0,
        m_width, m_depth,
        m_scale,
        1337
    );

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float halfWidth = m_width / 2.0f;
    float halfDepth = m_depth / 2.0f;

    for (int z = 0; z < m_depth; ++z)
    {
        for (int x = 0; x < m_width; ++x)
        {
            float heightValue = m_heightMap[z * m_width + x] * m_heightMultiplier;
            float posX = x - halfWidth;
            float posZ = z - halfDepth;

            vertices.push_back(Vertex{
                glm::vec3(posX, heightValue, posZ),
                glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec2(x / (float)m_width, z / (float)m_depth)
                });
        }
    }

    for (int z = 0; z < m_depth - 1; ++z)
    {
        for (int x = 0; x < m_width - 1; ++x)
        {
            int topLeft = z * m_width + x;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + m_width;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

Mesh* TerrainGenerator::GetMesh()
{
    return m_mesh.get();
}

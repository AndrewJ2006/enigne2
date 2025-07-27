#pragma once

#include <FastNoise/FastNoise.h>
#include <Mesh.h>  // Adjust path based on your project
#include <vector>
#include <memory>

class TerrainGenerator
{
public:
    TerrainGenerator(int width, int depth, float scale, float heightMultiplier);

    void Generate();
    Mesh* GetMesh();  // Add this line

private:
    int m_width;
    int m_depth;
    float m_scale;
    float m_heightMultiplier;

    std::vector<float> m_heightMap;
    std::unique_ptr<Mesh> m_mesh;  // Store generated mesh here
};

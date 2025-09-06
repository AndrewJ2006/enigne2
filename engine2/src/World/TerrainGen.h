#pragma once

#include <FastNoise/FastNoise.h>
#include <Mesh.h>  
#include <vector>
#include <memory>

class TerrainGenerator
{
public:
    TerrainGenerator(int width, int depth, float scale, float heightMultiplier);

    void Generate();
    Mesh* GetMesh(); 

private:
    int m_width;
    int m_depth;
    float m_scale;
    float m_heightMultiplier;

    std::vector<float> m_heightMap;
    std::unique_ptr<Mesh> m_mesh;  
};

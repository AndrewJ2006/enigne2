#pragma once
#include <memory>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Vertex.h"

class Renderer {
public:
    static bool Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    static void Draw();
    static void Shutdown();

private:
    static std::unique_ptr<Mesh> s_planeMesh;
    static std::unique_ptr<Shader> s_shader;
};

#pragma once
#include <memory>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Vertex.h"
#include <glm/glm.hpp>

class Renderer {
public:
    static bool Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    static void Draw();          // <-- this Draw() matches main.cpp call
    static void Shutdown();

    // Optional: You can also keep DrawScene if you want
    static void DrawScene(const glm::mat4& view, const glm::mat4& projection);

private:
    static std::unique_ptr<Mesh> s_planeMesh;
    static std::unique_ptr<Shader> s_shader;
};

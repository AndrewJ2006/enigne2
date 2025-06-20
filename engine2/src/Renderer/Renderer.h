#pragma once
#include <memory>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Vertex.h"
#include <glm/glm.hpp>

class Renderer {
public:
    static bool Init();  
    static void Draw();
    static void Shutdown();

    static void DrawScene(const glm::mat4& view, const glm::mat4& projection);

private:
    static std::unique_ptr<Mesh> s_planeMesh;
    static std::unique_ptr<Shader> s_shader;
};

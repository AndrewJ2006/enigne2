#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"

class Renderer {
public:
    static bool Init();
    static void DrawScene(const glm::mat4& view, const glm::mat4& projection);
    static void Shutdown();

    static Shader* GetShader() { return s_shader.get(); }
    static Mesh* GetMesh() { return s_cubeMesh.get(); }

private:
    static std::unique_ptr<Mesh> s_cubeMesh;
    static std::unique_ptr<Shader> s_shader;
};

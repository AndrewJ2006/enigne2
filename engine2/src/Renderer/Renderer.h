#pragma once

#include <memory>
#include <glm/glm.hpp>

class Mesh;
class Shader;

class Renderer {
public:
    static bool Init();
    static void DrawScene(const glm::mat4& view, const glm::mat4& projection);
    static void Shutdown();

    static Shader* GetShader();
    static Mesh* GetCubeMesh();

private:
    static std::unique_ptr<Mesh> s_cubeMesh;
    static std::unique_ptr<Shader> s_shader;
};

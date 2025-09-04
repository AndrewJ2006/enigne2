#pragma once

#include <memory>
#include <glm/glm.hpp>

class Mesh;
class Shader;
class World;

class Renderer {
public:
    
    static bool Init();

    
    static void DrawScene(const glm::mat4& view, const glm::mat4& projection, World& world);

    
    static void Shutdown();

    
    static Shader* GetShader();

private:
    static std::unique_ptr<Shader> s_shader;

    
};

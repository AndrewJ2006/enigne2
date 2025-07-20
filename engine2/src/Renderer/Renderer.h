#pragma once

#include <memory>
#include <glm/glm.hpp>

class Mesh;
class Shader;
class World;

class Renderer {
public:
    // Initialize rendering resources (shaders, etc.)
    static bool Init();

    // Draw the given world scene with specified camera matrices
    static void DrawScene(const glm::mat4& view, const glm::mat4& projection, World& world);

    // Clean up all allocated resources
    static void Shutdown();

    // Accessor to current shader (optional)
    static Shader* GetShader();

private:
    static std::unique_ptr<Shader> s_shader;

    // Add other static resources here as needed, e.g., meshes or textures
};

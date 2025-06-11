#include "Renderer.h"
#include <glad/glad.h>

// Static plane mesh
static std::unique_ptr<Mesh> s_planeMesh;

namespace Renderer {

    void Init() {
        std::vector<Vertex> vertices = {
            // Position             // Normal            // TexCoords
            {{-0.5f, 0.0f, -0.5f}, {0, 1, 0}, {0.0f, 0.0f}},
            {{ 0.5f, 0.0f, -0.5f}, {0, 1, 0}, {1.0f, 0.0f}},
            {{ 0.5f, 0.0f,  0.5f}, {0, 1, 0}, {1.0f, 1.0f}},
            {{-0.5f, 0.0f,  0.5f}, {0, 1, 0}, {0.0f, 1.0f}}
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0
        };

        s_planeMesh = std::make_unique<Mesh>(vertices, indices);
    }

    void Draw() {
        if (s_planeMesh)
            s_planeMesh->Draw();
    }

    void Shutdown() {
        s_planeMesh.reset();
    }
}

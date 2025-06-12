#include "Backend/Backend.h"
#include "Renderer.h"
#include <iostream>
#include "Objects.hpp"

int main() {
    std::cout << "Starting...\n";

    if (!BackEnd::Init(API::OPENGL, WindowedMode::WINDOWED)) {
        std::cerr << "BackEnd::Init() FAILED!\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glDisable(GL_CULL_FACE); // Optional: Disable backface culling for debugging

    std::vector<Vertex> vertices = Hardcoded::GetPlaneVertices();
    std::vector<unsigned int> indices = Hardcoded::GetPlaneIndices();

    if (!Renderer::Init(vertices, indices)) {
        std::cerr << "Renderer::Init() FAILED!\n";
        return -1;
    }

    while (BackEnd::WindowIsOpen()) {
        BackEnd::UpdateSubSystems();
        BackEnd::BeginFrame();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer::Draw();

        BackEnd::EndFrame();
    }

    Renderer::Shutdown();

    return 0;
}

#include "Backend.h"
#include "Renderer.h"
#include "Game.h"
#include "Objects.hpp"
#include <iostream>

int main() {
    std::cout << "Starting...\n";

    if (!Backend::Init(API::OPENGL, WindowedMode::WINDOWED)) {
        std::cerr << "Backend::Init() FAILED!\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    std::vector<Vertex> vertices = Hardcoded::GetPlaneVertices();
    std::vector<unsigned int> indices = Hardcoded::GetPlaneIndices();

    if (!Renderer::Init(vertices, indices)) {
        std::cerr << "Renderer::Init() FAILED!\n";
        return -1;
    }

    Game game;
    game.Init();

    while (!Backend::WindowShouldClose()) {
        Backend::UpdateSubSystems();
        Backend::BeginFrame();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float deltaTime = Backend::GetDeltaTime();
        game.Update(deltaTime);  // update camera, input, etc
        game.Render();           // render scene using current camera

        Backend::EndFrame();
    }

    Renderer::Shutdown();

    return 0;
}

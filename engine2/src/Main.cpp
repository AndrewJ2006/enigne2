#include "Backend/Backend.h"
#include <iostream>

int main() {
    std::cout << "Starting the OpenGL program...\n";

    if (!BackEnd::Init(API::OPENGL, WindowedMode::WINDOWED)) {
        std::cout << "BackEnd::Init() FAILED!\n";
        return -1;
    }

    while (BackEnd::WindowIsOpen()) {
        BackEnd::UpdateSubSystems();
        BackEnd::BeginFrame();

        // For now, just clear the screen with a color
        // You can add rendering calls later
        // (This could be in Backend or Renderer later)
        // For example: glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        //              glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BackEnd::EndFrame();
    }

    return 0;
}

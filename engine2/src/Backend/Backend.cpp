#include "Backend.h"
#include "GLWindow.h"

static GLWindow g_window;

bool BackEnd::Init(API api, WindowedMode mode) {
    if (api != API::OPENGL)
        return false;

    if (!g_window.CreateWindow(1280, 720, "My OpenGL Window", mode)) {
        return false;
    }

    return true;
}

void BackEnd::UpdateSubSystems() {
    g_window.PollEvents();
}

void BackEnd::BeginFrame() {
    g_window.BeginFrame();
}

void BackEnd::EndFrame() {
    g_window.SwapBuffers();
}

bool BackEnd::WindowIsOpen() {
    return !g_window.ShouldClose();
}

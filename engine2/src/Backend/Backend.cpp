#include "Backend.h"
#include "GLWindow.h"

static GLWindow g_window;

bool BackEnd::Init(API api, WindowedMode mode) {
    // For now, only support OpenGL
    if (api != API::OPENGL) return false;

    if (!g_window.CreateWindow(1280, 720, "My OpenGL Window", mode)) {
        return false;
    }
    // Initialize other subsystems if any
    return true;
}

void BackEnd::UpdateSubSystems() {
    // Update input, timers, etc.
    g_window.PollEvents();
}

void BackEnd::BeginFrame() {
    // Clear buffers etc.
    g_window.BeginFrame();
}

void BackEnd::EndFrame() {
    g_window.SwapBuffers();
}

bool BackEnd::WindowIsOpen() {
    return !g_window.ShouldClose();
}

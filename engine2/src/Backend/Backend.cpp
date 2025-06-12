// Backend.cpp
#include "Backend.h"
#include "GLWindow.h"

static GLWindow g_window;

static float s_lastTime = 0.0f;
static float s_deltaTime = 0.0f;

static double s_lastMouseX = 0.0;
static double s_lastMouseY = 0.0;
static bool s_firstMouse = true;
static float s_mouseDeltaX = 0.0f;
static float s_mouseDeltaY = 0.0f;

bool Backend::Init(API api, WindowedMode mode) {
    if (api != API::OPENGL)
        return false;

    if (!g_window.CreateWindow(1280, 720, "My OpenGL Window", mode)) {
        return false;
    }

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(g_window.GetGLFWWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetCursorPosCallback(g_window.GetGLFWWindow(), [](GLFWwindow* window, double xpos, double ypos) {
        if (s_firstMouse) {
            s_lastMouseX = xpos;
            s_lastMouseY = ypos;
            s_firstMouse = false;
        }

        s_mouseDeltaX = static_cast<float>(xpos - s_lastMouseX);
        s_mouseDeltaY = static_cast<float>(s_lastMouseY - ypos);

        s_lastMouseX = xpos;
        s_lastMouseY = ypos;
        });

    s_lastTime = static_cast<float>(glfwGetTime());
    return true;
}

void Backend::UpdateSubSystems() {
    g_window.PollEvents();

    float currentTime = static_cast<float>(glfwGetTime());
    s_deltaTime = currentTime - s_lastTime;
    s_lastTime = currentTime;
}

void Backend::BeginFrame() {
    g_window.BeginFrame();
}

void Backend::EndFrame() {
    g_window.SwapBuffers();
    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;
}

bool Backend::WindowShouldClose() {
    return g_window.ShouldClose();
}

bool Backend::IsKeyPressed(int key) {
    return glfwGetKey(g_window.GetGLFWWindow(), key) == GLFW_PRESS;
}

void Backend::GetMouseDelta(float& xOffset, float& yOffset) {
    xOffset = s_mouseDeltaX;
    yOffset = s_mouseDeltaY;
}

void Backend::SetMousePosition(float xpos, float ypos) {
    glfwSetCursorPos(g_window.GetGLFWWindow(), xpos, ypos);
}

void Backend::EnableRawMouseMotion(bool enable) {
    glfwSetInputMode(g_window.GetGLFWWindow(), GLFW_RAW_MOUSE_MOTION, enable ? GLFW_TRUE : GLFW_FALSE);
}

float Backend::GetDeltaTime() {
    return s_deltaTime;
}

float Backend::GetAspectRatio() {
    int width, height;
    g_window.GetFramebufferSize(width, height);
    return (height == 0) ? 1.0f : static_cast<float>(width) / static_cast<float>(height);
}

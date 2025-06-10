#include "GLWindow.h"
#include <GLFW/glfw3.h>

static GLFWwindow* window = nullptr;

bool GLWindow::CreateWindow(int width, int height, const std::string& title, WindowedMode mode) {
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    return true;
}

void GLWindow::PollEvents() {
    glfwPollEvents();
}

void GLWindow::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::SwapBuffers() {
    glfwSwapBuffers(window);
}

bool GLWindow::ShouldClose() {
    return glfwWindowShouldClose(window);
}

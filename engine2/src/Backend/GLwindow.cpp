#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GLWindow.h"


bool GLWindow::CreateWindow(int width, int height, const std::string& title, WindowedMode mode) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // TODO: Handle fullscreen using mode if needed
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

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

GLWindow::~GLWindow() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

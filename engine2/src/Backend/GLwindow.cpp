#include "GLWindow.h"
#include <iostream>

GLWindow::GLWindow() : m_window(nullptr) {}

GLWindow::~GLWindow() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

bool GLWindow::CreateWindow(int width, int height, const char* title, WindowedMode mode) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(width, height, title,
        mode == WindowedMode::FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr,
        nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    glfwSwapInterval(1); // vsync

    return true;
}

void GLWindow::PollEvents() {
    glfwPollEvents();
}

void GLWindow::SwapBuffers() {
    if (m_window)
        glfwSwapBuffers(m_window);
}

void GLWindow::BeginFrame() {
}

bool GLWindow::ShouldClose() {
    return m_window ? glfwWindowShouldClose(m_window) : true;
}

GLFWwindow* GLWindow::GetGLFWWindow() const {
    return m_window;
}

void GLWindow::GetFramebufferSize(int& width, int& height) const {
    if (m_window)
        glfwGetFramebufferSize(m_window, &width, &height);
    else {
        width = 0;
        height = 0;
    }
}

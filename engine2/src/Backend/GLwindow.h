#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Backend.h"  

class GLWindow {
public:
    GLWindow();
    ~GLWindow();

    bool CreateWindow(int width, int height, const char* title, WindowedMode mode);
    void PollEvents();
    void SwapBuffers();
    void BeginFrame();
    bool ShouldClose();

    GLFWwindow* GetGLFWWindow() const;
    void GetFramebufferSize(int& width, int& height) const;

private:
    GLFWwindow* m_window = nullptr;
};

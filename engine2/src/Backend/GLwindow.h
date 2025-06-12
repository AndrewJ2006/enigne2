#pragma once
#include <string>

enum class WindowedMode;

class GLWindow {
public:
    bool CreateWindow(int width, int height, const std::string& title, WindowedMode mode);
    void PollEvents();
    void BeginFrame();
    void SwapBuffers();
    bool ShouldClose();
    bool IsKeyPressed(int key);
    ~GLWindow();

private:
    struct GLFWwindow* window = nullptr;
};
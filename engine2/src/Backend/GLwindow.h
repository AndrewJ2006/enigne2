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

private:
    // Store GLFWwindow* or your window handle here
};

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

    ~GLWindow();  // Destructor for cleanup

private:
    struct GLFWwindow* window = nullptr;
};

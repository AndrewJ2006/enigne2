#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class API {
    OPENGL,
    VULKAN,
};

enum class WindowedMode {
    WINDOWED,
    FULLSCREEN
};

namespace Backend {
    bool Init(API api, WindowedMode mode);
    void UpdateSubSystems();
    void BeginFrame();
    void EndFrame();
    bool WindowShouldClose();

    bool IsKeyPressed(int key);
    void GetMouseDelta(float& xOffset, float& yOffset);
    void SetMousePosition(float xpos, float ypos);
    void EnableRawMouseMotion(bool enable);

    float GetDeltaTime();
    float GetAspectRatio();
}

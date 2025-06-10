// Backend.h
#pragma once

enum class API {
    OPENGL,
    VULKAN,
    // ...
};

enum class WindowedMode {
    WINDOWED,
    FULLSCREEN
};

namespace BackEnd {
    bool Init(API api, WindowedMode mode);
    void UpdateSubSystems();
    void BeginFrame();
    void EndFrame();
    bool WindowIsOpen();
}

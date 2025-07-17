#pragma once

class ScenePx {
public:
    ScenePx();
    ~ScenePx();

    static void CreateStaticFloor(); // Static so it can be called without an instance
    static bool Init();              // Optional: make Init static if used that way

private:
    // Add your private members here
};

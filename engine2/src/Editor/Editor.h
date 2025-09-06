#pragma once

#include "CameraEditor.h"

class Editor {
public:
    Editor() : m_camera(nullptr) {}          

    explicit Editor(Camera* cam) : m_camera(cam) {}

    void SetCamera(Camera* camera) { m_camera = camera; }

    void Update(float deltaTime);

private:
    void PerformRaycast();

    Camera* m_camera;
};

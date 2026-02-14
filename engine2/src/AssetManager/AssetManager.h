#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Base/Types.h"

class Model;

class AssetManager {
public:
    static void Init();
    static std::shared_ptr<Model> LoadModel(const std::string& path);
};

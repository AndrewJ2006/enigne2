#include "AssetManager.h"
#include "Model.h"
#include <memory>
#include <iostream>

std::shared_ptr<Model> AssetManager::LoadModel(const std::string& path) {
    std::cout << "[AssetManager] Loading model: " << path << "\n";
    return std::make_shared<Model>(path);
}

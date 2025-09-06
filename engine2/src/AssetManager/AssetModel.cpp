// AssetModel.cpp
#include "AssetManager.h"
#include <memory>

std::shared_ptr<Model> AssetModel::LoadAK47Model() {
    static const std::string modelPath = "Models/ak_47.fbx";
    return std::make_shared<Model>(modelPath);
}

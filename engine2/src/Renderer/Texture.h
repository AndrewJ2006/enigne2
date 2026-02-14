#pragma once

#include <string>

struct Texture {
    unsigned int id = 0;
    std::string type;
    std::string path;
};

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

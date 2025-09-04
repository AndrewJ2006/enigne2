#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void Use() const;

    void SetMat4(const std::string& name, const glm::mat4& mat) const;
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;       
    void SetVec3(const std::string& name, const glm::vec3& value) const;
};

#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp> 
#include <glm/gtc/quaternion.hpp>      

struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f); 
    glm::vec3 scale = glm::vec3(1.0f);

    glm::mat4 to_mat4() const {
        glm::mat4 mat(1.0f);

        mat = glm::scale(mat, scale);
        mat = glm::rotate(mat, rotation.z, glm::vec3(0, 0, 1));
        mat = glm::rotate(mat, rotation.y, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, rotation.x, glm::vec3(1, 0, 0));
        mat = glm::translate(glm::mat4(1.0f), position) * mat;

        return mat;
    }

    void from_mat4(const glm::mat4& mat) {
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::quat orientation;
        glm::decompose(mat, scale, orientation, position, skew, perspective);
        rotation = glm::eulerAngles(orientation);
    }
};

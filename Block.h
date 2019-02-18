#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <vector>
#include "glm/vec3.hpp"
#include "Vertex.h"

namespace VkVoxel {
    const static std::vector<glm::vec3> FRONT_FACE = {
        { -0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }
    };
    const static std::vector<glm::vec3> LEFT_FACE = {
        { -0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f,  0.5f }
    };
    const static std::vector<glm::vec3> RIGHT_FACE = {
        {  0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f,  0.5f }, { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, -0.5f }
    };
    const static std::vector<glm::vec3> BACK_FACE = {
        {  0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }
    };
    const static std::vector<glm::vec3> TOP_FACE = {
        { -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }
    };
    const static std::vector<glm::vec3> BOTTOM_FACE = {
        { -0.5f, -0.5f,  0.5f }, {  0.5f, -0.5f,  0.5f }, {  0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }
    };
};

#endif

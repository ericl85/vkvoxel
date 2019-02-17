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

    const static std::vector<Vertex> BLOCK_VERTICES = {
        // FRONT FACE
        {{ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }},
        {{  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
        {{  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.5f }},
        {{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }},
        // LEFT FACE
        {{ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }},
        {{ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
        {{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.5f }},
        {{ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }},
        // RIGHT FACE
        {{  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }},
        {{  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.5f }},
        {{  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }},
        // BACK FACE    
        {{  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }},
        {{ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
        {{ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.5f }},
        {{  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }},
        // TOP FACE
        {{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }},
        {{  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.5f }},
        {{ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }},
        // BOTTOM FACE
        {{ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }},
        {{  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.5f }},
        {{ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f }}
    };

    const static std::vector<uint32_t> BLOCK_INDICES = {
         0,  3,  2,  2,  1,  0, // FRONT FACE
         4,  7,  6,  6,  5,  4, // LEFT FACE
         8,  11, 10, 10, 9,  8, // RIGHT FACE
        12, 15, 14, 14, 13, 12, // BACK FACE
        16, 19, 18, 18, 17, 16, // TOP FACE
        20, 23, 22, 22, 21, 20  // BOTTOM FACE
    };
};

#endif

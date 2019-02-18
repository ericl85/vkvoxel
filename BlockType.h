#ifndef __BLOCK_TYPE_H_
#define __BLOCK_TYPE_H_

#include <vector>
#include "glm/vec3.hpp"
#include "Vertex.h"

namespace VkVoxel {

    class BlockType {
    public:
        BlockType();

        uint32_t frontTexture = 0;
        glm::vec3 frontColor = { 1.0f, 1.0f, 1.0f };

        uint32_t leftTexture = 0;
        glm::vec3 leftColor = { 1.0f, 1.0f, 1.0f };

        uint32_t rightTexture = 0;
        glm::vec3 rightColor = { 1.0f, 1.0f, 1.0f };

        uint32_t backTexture = 0;
        glm::vec3 backColor = { 1.0f, 1.0f, 1.0f };

        uint32_t topTexture = 0;
        glm::vec3 topColor = { 1.0f, 1.0f, 1.0f };

        uint32_t bottomTexture = 0;
        glm::vec3 bottomColor = { 1.0f, 1.0f, 1.0f };

    };
};

#endif
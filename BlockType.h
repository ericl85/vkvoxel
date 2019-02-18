#ifndef __BLOCK_TYPE_H_
#define __BLOCK_TYPE_H_

#include <vector>
#include "glm/vec2.hpp"
#include "Vertex.h"

namespace VkVoxel {

    class BlockType {
    public:
        BlockType();

        int id;
        uint32_t frontTexture = 0;
        uint32_t leftTexture = 0;
        uint32_t rightTexture = 0;
        uint32_t backTexture = 0;
        uint32_t topTexture = 0;
        uint32_t bottomTexture = 0;

        std::vector<Vertex> vertexes;
    };
};

#endif
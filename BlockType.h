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
        std::vector<Vertex> vertexes;
    };
};

#endif
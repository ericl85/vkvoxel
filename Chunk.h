#ifndef __CHUNK_H_
#define __CHUNK_H_

#include <cstdint>
#include <vector>
#include "glm/mat4x4.hpp"
#include "BlockType.h"
#include "Vertex.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 128

namespace VkVoxel {
    class Chunk {
    public:
        Chunk(uint32_t x, uint32_t y);
        void build(const std::vector<BlockType>& blockTypes);
        virtual void cleanup() = 0;

        glm::mat4x4 model;

        uint32_t blocks[CHUNK_HEIGHT][CHUNK_SIZE][CHUNK_SIZE];

        uint32_t getVertexCount();
        uint32_t getIndexCount();

    protected:
        virtual void prepare(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) = 0;

    private:
        uint32_t _xPos;
        uint32_t _yPos;
        size_t _lastSize;
        uint32_t _vertexCount;
        uint32_t _indexCount;
    };
}

#endif

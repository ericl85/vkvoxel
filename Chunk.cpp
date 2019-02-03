#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Block.h"
#include "Chunk.h"

namespace VkVoxel {
    Chunk::Chunk(uint32_t x, uint32_t z) {
        model = glm::mat4x4(1.0f);

        // Zero out the blocks
        for (int yBlock = 0; yBlock < CHUNK_HEIGHT; yBlock++) {
            for (int xBlock = 0; xBlock < CHUNK_SIZE; xBlock++) {
                for (int zBlock = 0; zBlock < CHUNK_SIZE; zBlock++) {
                    blocks[yBlock][xBlock][zBlock] = 0;
                }
            }
        }
        _lastSize = 0;
    }

    void Chunk::build(const std::vector<BlockType>& blockTypes) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        vertices.reserve(_lastSize * BLOCK_VERTICES.size());
        indices.reserve(_lastSize * BLOCK_VERTICES.size());

        _vertexCount = 0;
        _indexCount = 0;
        size_t newSize = 0;
        for (int yBlock = 0; yBlock < CHUNK_HEIGHT; yBlock++) {
            for (int xBlock = 0; xBlock < CHUNK_SIZE; xBlock++) {
                for (int zBlock = 0; zBlock < CHUNK_SIZE; zBlock++) {
                    uint32_t blockIndex = blocks[yBlock][xBlock][zBlock];
                    if (blockIndex > 0) {
                        BlockType blockType = blockTypes[blockIndex];

                        for (auto it = blockType.vertexes.begin(); it != blockType.vertexes.end(); it++) {
                            // Make a copy of the block from the block type with it's position translated
                            Vertex blockVertex;
                            blockVertex.pos = (*it).pos + (glm::vec3(xBlock, yBlock, zBlock) * 2.0f);
                            blockVertex.color = glm::vec3((*it).color);
                            blockVertex.texCoord = glm::vec2((*it).texCoord);

                            vertices.push_back(blockVertex);
                            _vertexCount++;
                        }

                        for (size_t i = 0; i < BLOCK_INDICES.size(); i++) {
                            // Make a copy of the indices with the index into the vertices translated by how many blocks are
                            // currently in the chunk.
                            uint32_t blockIndex = BLOCK_INDICES[i] + (BLOCK_VERTICES.size() * newSize);
                            indices.push_back(blockIndex);
                            _indexCount++;
                        }

                        newSize++;
                    }
                }
            }
        }

        // We'll cache the size so we know how much memory to reserve for the next build
        _lastSize = newSize;

        // Now call the implementation of the build buffers method.
        prepare(vertices, indices);
    }

    uint32_t Chunk::getVertexCount() {
        return _vertexCount;
    }

    uint32_t Chunk::getIndexCount() {
        return _indexCount;
    }
}

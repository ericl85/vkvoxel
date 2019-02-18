#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Block.h"
#include "Chunk.h"

namespace VkVoxel {
    Chunk::Chunk(int x, int z) {
        _model = glm::mat4x4(1.0f);
        _model = glm::translate(_model, glm::vec3((float)(x * CHUNK_SIZE), 0, (float)(z * CHUNK_SIZE)));

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
        vertices.reserve(_lastSize);
        indices.reserve(_lastSize);

        _vertexCount = 0;
        _indexCount = 0;
        for (int yBlock = 0; yBlock < CHUNK_HEIGHT; yBlock++) {
            for (int xBlock = 0; xBlock < CHUNK_SIZE; xBlock++) {
                for (int zBlock = 0; zBlock < CHUNK_SIZE; zBlock++) {
                    uint32_t blockIndex = blocks[yBlock][xBlock][zBlock];
                    if (blockIndex > 0) {
                        BlockType blockType = blockTypes[blockIndex];

                        glm::vec3 blockTranslation = glm::vec3(xBlock, yBlock, zBlock);

                        // Front face neighbor test: if we're at the front or if the block in front of us is air, we add the front vertices
                        if (zBlock == 0 || blocks[yBlock][xBlock][zBlock - 1] == 0) {
                            vertices.push_back({ FRONT_FACE[0] + blockTranslation, blockType.frontColor, glm::vec3(0.0f, 1.0f, blockType.frontTexture) });
                            vertices.push_back({ FRONT_FACE[1] + blockTranslation, blockType.frontColor, glm::vec3(1.0f, 1.0f, blockType.frontTexture) });
                            vertices.push_back({ FRONT_FACE[2] + blockTranslation, blockType.frontColor, glm::vec3(1.0f, 0.0f, blockType.frontTexture) });
                            vertices.push_back({ FRONT_FACE[3] + blockTranslation, blockType.frontColor, glm::vec3(0.0f, 0.0f, blockType.frontTexture) });

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Left face neighbor test
                        if (xBlock == 0 || blocks[yBlock][xBlock - 1][zBlock] == 0) {
                            vertices.push_back({ LEFT_FACE[0] + blockTranslation, blockType.leftColor, glm::vec3(0.0f, 1.0f, blockType.leftTexture) });
                            vertices.push_back({ LEFT_FACE[1] + blockTranslation, blockType.leftColor, glm::vec3(1.0f, 1.0f, blockType.leftTexture) });
                            vertices.push_back({ LEFT_FACE[2] + blockTranslation, blockType.leftColor, glm::vec3(1.0f, 0.0f, blockType.leftTexture) });
                            vertices.push_back({ LEFT_FACE[3] + blockTranslation, blockType.leftColor, glm::vec3(0.0f, 0.0f, blockType.leftTexture) });

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Right face neighbor test
                        if (xBlock == (CHUNK_SIZE - 1) || blocks[yBlock][xBlock + 1][zBlock] == 0) {
                            vertices.push_back({ RIGHT_FACE[0] + blockTranslation, blockType.rightColor,  glm::vec3(0.0f, 1.0f, blockType.rightTexture) });
                            vertices.push_back({ RIGHT_FACE[1] + blockTranslation, blockType.rightColor,  glm::vec3(1.0f, 1.0f, blockType.rightTexture) });
                            vertices.push_back({ RIGHT_FACE[2] + blockTranslation, blockType.rightColor, glm::vec3(1.0f, 0.0f, blockType.rightTexture) });
                            vertices.push_back({ RIGHT_FACE[3] + blockTranslation, blockType.rightColor, glm::vec3(0.0f, 0.0f, blockType.rightTexture) });

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Back face neighbor test
                        if (zBlock == (CHUNK_SIZE - 1) || blocks[yBlock][xBlock][zBlock + 1] == 0) {
                            vertices.push_back({ BACK_FACE[0] + blockTranslation, blockType.backColor, glm::vec3(0.0f, 1.0f, blockType.backTexture) });
                            vertices.push_back({ BACK_FACE[1] + blockTranslation, blockType.backColor, glm::vec3(1.0f, 1.0f, blockType.backTexture) });
                            vertices.push_back({ BACK_FACE[2] + blockTranslation, blockType.backColor, glm::vec3(1.0f, 0.0f, blockType.backTexture) });
                            vertices.push_back({ BACK_FACE[3] + blockTranslation, blockType.backColor, glm::vec3(0.0f, 0.0f, blockType.backTexture) });

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Top face neighbor test
                        if (yBlock == (CHUNK_HEIGHT - 1) || blocks[yBlock + 1][xBlock][zBlock] == 0) {
                            vertices.push_back({ TOP_FACE[0] + blockTranslation, blockType.topColor, glm::vec3(0.0f, 1.0f, blockType.topTexture) });
                            vertices.push_back({ TOP_FACE[1] + blockTranslation, blockType.topColor, glm::vec3(1.0f, 1.0f, blockType.topTexture) });
                            vertices.push_back({ TOP_FACE[2] + blockTranslation, blockType.topColor, glm::vec3(1.0f, 0.0f, blockType.topTexture) });
                            vertices.push_back({ TOP_FACE[3] + blockTranslation, blockType.topColor, glm::vec3(0.0f, 0.0f, blockType.topTexture) });

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Bottom face neighbor test
                        if (yBlock == 0 || blocks[yBlock - 1][xBlock][zBlock] == 0) {
                            vertices.push_back({ BOTTOM_FACE[0] + blockTranslation, blockType.bottomColor, glm::vec3(0.0f, 1.0f, blockType.bottomTexture) });
                            vertices.push_back({ BOTTOM_FACE[1] + blockTranslation, blockType.bottomColor, glm::vec3(1.0f, 1.0f, blockType.bottomTexture) });
                            vertices.push_back({ BOTTOM_FACE[2] + blockTranslation, blockType.bottomColor, glm::vec3(1.0f, 0.0f, blockType.bottomTexture) });
                            vertices.push_back({ BOTTOM_FACE[3] + blockTranslation, blockType.bottomColor, glm::vec3(0.0f, 0.0f, blockType.bottomTexture) });

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }
                    }
                }
            }
        }

        // We'll cache the size so we know how much memory to reserve for the next build
        _lastSize = vertices.size();

        // Now call the implementation of the build buffers method.
        prepare(vertices, indices);
    }

    glm::mat4x4 Chunk::getTransform(const glm::mat4x4& proj, const glm::mat4x4& view) {
        return (proj * view * _model);
    }

    uint32_t Chunk::getVertexCount() {
        return _vertexCount;
    }

    uint32_t Chunk::getIndexCount() {
        return _indexCount;
    }
}

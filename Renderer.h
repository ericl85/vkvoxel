#ifndef __RENDERER_H_
#define __RENDERER_H_

#include <memory>

#include "Camera.h"
#include "Chunk.h"
#include "TextureAtlas.h"

namespace VkVoxel {
    class Renderer {
    public:
        Renderer();
        ~Renderer();

        virtual void initialize() = 0;
        virtual void cleanup() = 0;
        virtual void render() = 0;
        virtual void waitIdle() = 0;

        virtual std::shared_ptr<Chunk> createChunk(int x, int y) = 0;
        virtual std::shared_ptr<TextureAtlas> createTextureAtlas() = 0;
        virtual void setChunks(const std::vector<std::shared_ptr<Chunk>>& chunkList) = 0;

        std::shared_ptr<Camera> getCamera();
        void setCamera(std::shared_ptr<Camera> camera);

        void addBlockType(BlockType blockType);

    protected:
        std::shared_ptr<Camera> _camera;
        std::vector<BlockType> blockTypes = { {} };
    };
};

#endif

#include "Renderer.h"

namespace VkVoxel {
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {

    }

    void Renderer::setCamera(std::shared_ptr<Camera> camera) {
        _camera = camera;
    }

    std::shared_ptr<Camera> Renderer::getCamera() {
        return _camera;
    }

    void Renderer::addBlockType(BlockType blockType) {
        blockTypes.push_back(blockType);
    }
}

#ifndef __WORLD_H_
#define __WORLD_H_

#include <chrono>
#include <memory>

#include "Chunk.h"
#include "Renderer.h"
#include "InputState.h"

namespace VkVoxel {
    class World {
    public:
        void initialize(std::shared_ptr<Renderer> renderer, std::shared_ptr<Camera> camera);
        void update(InputState inputState);
        void render();

    private:
        std::chrono::time_point<std::chrono::steady_clock> _lastTime;

        std::shared_ptr<Renderer> _renderer;
        std::vector<std::shared_ptr<Chunk>> _chunks;
        std::shared_ptr<Camera> _camera;
    };
}

#endif

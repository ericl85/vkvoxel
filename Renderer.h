#ifndef __RENDERER_H_
#define __RENDERER_H_

#include <memory>

#include "Camera.h"

namespace VkVoxel {
    class Renderer {
    public:
        Renderer();
        ~Renderer();

        virtual void initialize() = 0;
        virtual void cleanup() = 0;
        virtual void render() = 0;

        std::shared_ptr<Camera> getCamera();
        void setCamera(std::shared_ptr<Camera> camera);

    protected:
        std::shared_ptr<Camera> _camera;
    };
};

#endif

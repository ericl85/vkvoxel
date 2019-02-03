#ifndef __VK_VOXEL_APPLICATION_
#define __VK_VOXEL_APPLICATION_

#include "VkRenderer.h"

namespace VkVoxel {
    class VkVoxelApplication {
    public:
        void run();

    private:
        void init();
        void mainLoop();
        void cleanup();

        VkRenderer renderer;
        std::shared_ptr<Camera> camera;
        GLFWwindow* window;
    };
}

#endif

#ifndef __VK_VOXEL_APPLICATION_
#define __VK_VOXEL_APPLICATION_

#include "VkRenderer.h"

namespace VkVoxel {
    class VkVoxelApplication {
    public:
        void run();

        void resizeFramebuffer();

    private:
        void init();
        void mainLoop();
        void cleanup();
        
        bool firstMouse = true;
        float lastMouseX;
        float lastMouseY;

        VkRenderer renderer;
        std::shared_ptr<Camera> camera;
        GLFWwindow* window;
    };
}

#endif

#include "glm/trigonometric.hpp"
#include "VkVoxelApplication.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace VkVoxel {
    void VkVoxelApplication::run() {
        init();
        mainLoop();
        cleanup();
    }

    void VkVoxelApplication::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera->move(glm::vec3(1.0f, 0.0f, 0.0f), 0.01f);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera->move(glm::vec3(-1.0f, 0.0f, 0.0f), 0.01f);
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera->move(glm::vec3(0.0f, 0.0f, 1.0f), 0.01f);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera->move(glm::vec3(0.0f, 0.0f, -1.0f), 0.01f);
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
                camera->move(glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
                camera->move(glm::vec3(0.0f, -1.0f, 0.0f), 0.01f);

            renderer.render();
        }
    }
    
    void VkVoxelApplication::init() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VkVoxel Application", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        renderer.setWindow(window);
        
        camera = std::make_shared<Camera>(WINDOW_WIDTH, WINDOW_HEIGHT);
        camera->setPosition(glm::vec3(0.0f, 0.0f, -24.0f));
        //camera->setRotation(glm::radians(-45.0f), glm::radians(0.0f));
        renderer.setCamera(camera);

        renderer.initialize();
    }

    void VkVoxelApplication::cleanup() {
        renderer.cleanup();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

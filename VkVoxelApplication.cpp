#include "glm/trigonometric.hpp"
#include "VkVoxelApplication.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool firstMouse = true;
float mouseX = WINDOW_WIDTH / 2;
float mouseY = WINDOW_HEIGHT / 2;
bool framebufferResized = false;

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    mouseX = (float)xPos;
    mouseY = (float)yPos;
}

namespace VkVoxel {
    void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<VkVoxelApplication*>(glfwGetWindowUserPointer(window));
        app->resizeFramebuffer();
    }
    
    void VkVoxelApplication::run() {
        init();
        mainLoop();
        cleanup();
    }

    void VkVoxelApplication::resizeFramebuffer() {
        renderer->framebufferResized = true;
    }

    void VkVoxelApplication::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            
            InputState inputState;

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                inputState.leftSpeed = 1.0f;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                inputState.rightSpeed = 1.0f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                inputState.forwardSpeed = 1.0f;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                inputState.backwardSpeed = 1.0f;

            if (firstMouse) {
                lastMouseX = mouseX;
                lastMouseY = mouseY;
                firstMouse = false;
            }

            float xOffset = mouseX - lastMouseX;
            float yOffset = lastMouseY - mouseY;

            inputState.yawSpeed = xOffset;
            inputState.pitchSpeed = yOffset;

            lastMouseX = mouseX;
            lastMouseY = mouseY;

            world.update(inputState);
            world.render();
        }
    }
    
    void VkVoxelApplication::init() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VkVoxel Application", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPosCallback(window, mouse_callback);

        renderer = std::make_shared<VkRenderer>();
        renderer->setWindow(window);
        
        camera = std::make_shared<Camera>(WINDOW_WIDTH, WINDOW_HEIGHT);
        camera->setPosition(glm::vec3(0.0f, 2.0f, -8.0f));

        renderer->initialize();
        world.initialize(renderer, camera);
    }

    void VkVoxelApplication::cleanup() {
        renderer->waitIdle();
        renderer->cleanup();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}


#include "glm/trigonometric.hpp"
#include "VkVoxelApplication.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool firstMouse = true;
float mouseX = WINDOW_WIDTH / 2;
float mouseY = WINDOW_HEIGHT / 2;

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    mouseX = (float)xPos;
    mouseY = (float)yPos;
}

namespace VkVoxel {
    void VkVoxelApplication::run() {
        init();
        mainLoop();
        cleanup();
    }

    void VkVoxelApplication::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            
            glm::vec3 cameraPos = camera->getPosition();
            glm::vec3 cameraFront = camera->getFront();

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                cameraPos -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * 0.01f;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * 0.01f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += cameraFront * 0.01f;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= cameraFront * 0.01f;
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
                cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * 0.01f;
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
                cameraPos -= glm::vec3(0.0f, 1.0f, 0.0f) * 0.01f;

            if (firstMouse) {
                lastMouseX = mouseX;
                lastMouseY = mouseY;
                firstMouse = false;
            }

            float xOffset = mouseX - lastMouseX;
            float yOffset = lastMouseY - mouseY;

            float yaw = camera->getYaw();
            float pitch = camera->getPitch();
            yaw += xOffset * 0.5f;
            pitch += yOffset * 0.5f;

            if (pitch > 89.0f) {
                pitch = 89.0f;
            }
            if (pitch < -89.0f) {
                pitch = -89.0f;
            }

            camera->setRotation(pitch, yaw);

            lastMouseX = mouseX;
            lastMouseY = mouseY;

            camera->setPosition(cameraPos);

            renderer.render();
        }
    }
    
    void VkVoxelApplication::init() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VkVoxel Application", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, mouse_callback);
        renderer.setWindow(window);
        
        camera = std::make_shared<Camera>(WINDOW_WIDTH, WINDOW_HEIGHT);
        camera->setPosition(glm::vec3(0.0f, 2.0f, -8.0f));
        renderer.setCamera(camera);

        renderer.initialize();
    }

    void VkVoxelApplication::cleanup() {
        renderer.cleanup();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}


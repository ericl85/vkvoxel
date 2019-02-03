#ifndef __VKRENDERER_H_
#define __VKRENDERER_H_

#include <vector>
#include <optional>

#include "VkManager.h"
#include "VkChunk.h"
#include "Camera.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>

#define MAX_FRAMES_IN_FLIGHT 2

namespace VkVoxel {
    class VkRenderer : public Renderer {
    public:
        virtual void cleanup();
        virtual void initialize();
        virtual void render();

        void setWindow(GLFWwindow* window);

    private:
        std::shared_ptr<VkManager> _manager;

        // Just testing with a single chunk for now
        VkChunk* chunk;
        void createChunk();

        // Window functions and members
        GLFWwindow* window = nullptr;

        // Vulkan initialization functions
        void createSurface(VkInstance instance);
        void createSwapChain();
        void createImageViews();
        void createDepthResources();
        void createRenderPass();
        void createDescriptorSetLayout();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSets();
        void createCommandBuffers();
        void createSyncObjects();

        // Cleanup
        void cleanupSwapChain();

        // Rendering
        void updateUniformBuffer(uint32_t imageIndex);
 
        // Vulkan utility functions
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
        VkShaderModule createShaderModule(const std::vector<char>& code);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VmaMemoryUsage memoryUsage, VkImage& image, VmaAllocation& imageAllocation);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

        // Vulkan constants
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
        };
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        bool enableValidationLayers;
        VkDebugUtilsMessengerEXT callback;
        VkSurfaceKHR surface;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        VkRenderPass renderPass;

        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VmaAllocation> uniformBufferAllocations;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        size_t currentFrame = 0;

        VkImage depthImage;
        VmaAllocation depthImageMemory;
        VkImageView depthImageView;

        std::vector<BlockType> blockTypes;

        bool framebufferResized;
    };
}

#endif

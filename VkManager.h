#ifndef __VK_MANAGER_H_
#define __VK_MANAGER_H_

#include <vector>
#include "vk_mem_alloc.h"
#include "VkUtil.h"

namespace VkVoxel {
    class VkManager {
    private:
        QueueFamilyIndices _queueFamilyIndices;
        
        VkInstance _instance;
        VkPhysicalDevice _physicalDevice;
        VkDevice _device;
        VkDebugUtilsMessengerEXT _callback;
        VmaAllocator _allocator;
        VkCommandPool _commandPool;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkDescriptorPool _descriptorPool;
        VkDescriptorSetLayout _descriptorSetLayout;
        
        // Initialization
        void createInstance();
        void setupDebugCallback();
        void pickPhysicalDevice(VkSurfaceKHR surface);
        void createLogicalDevice(VkSurfaceKHR surface);
        void createAllocator();
        void createCommandPool();
        void createDescriptorPool(uint32_t poolCount);
        void createDescriptorSetLayout();

        bool checkValidationLayerSupport();
        std::vector<const char *> getRequiredExtensions();
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
        bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        bool hasStencilComponent(VkFormat format);

        // Vulkan constants
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
        };
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        bool _enableValidationLayers;
        uint32_t _framesInFlight;
        uint32_t _currentFrame;

    public:
        void setupInstance(bool enableValidationLayers);
        void setupDevice(VkSurfaceKHR surface, uint32_t framesInFlight);
        void cleanup();
        void cleanupInstance();

        VkInstance getInstance();
        VkPhysicalDevice getPhysicalDevice();
        VkDevice getDevice();
        VmaAllocator getAllocator();
        VkCommandPool getCommandPool();
        VkQueue getGraphicsQueue();
        VkQueue getPresentQueue();
        VkDescriptorPool getDescriptorPool();

        uint32_t getFrameCount();
        void setCurrentFrame(uint32_t currentFrame);
        uint32_t getCurrentFrame();

        // Single time command buffer prep
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        // Image layout transition
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t layerCount);
    };
}

#endif
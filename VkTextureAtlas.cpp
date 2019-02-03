#include "VkTextureAtlas.h"

namespace VkVoxel {
    VkTextureAtlas::VkTextureAtlas(std::string fileName, std::shared_ptr<VkManager> manager) : TextureAtlas(fileName) {
        _manager = manager;
    }

    void VkTextureAtlas::prepare(uint32_t texWidth, uint32_t texHeight, int texChannels, stbi_uc* pixels) {
        VmaAllocator allocator = _manager->getAllocator();
        
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        // Create a staging buffer
        VkBuffer stagingBuffer;
        VmaAllocation stagingAllocation;
        VkBufferCreateInfo stagingCreateInfo = {};
        stagingCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        stagingCreateInfo.size = imageSize;
        stagingCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        VmaAllocationCreateInfo stagingAllocInfo = {};
        stagingAllocInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;

        // Copy the pixels to the staging buffer
        vmaCreateBuffer(allocator, &stagingCreateInfo, &stagingAllocInfo, &stagingBuffer, &stagingAllocation, nullptr);
        void* data;
        vmaMapMemory(allocator, stagingAllocation, &data);
        memcpy(data, pixels, (size_t)imageSize);
        vmaUnmapMemory(allocator, stagingAllocation);

        // Create the image
        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = texWidth;
        imageInfo.extent.height = texHeight;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

        VmaAllocationCreateInfo imageAllocationInfo = {};
        imageAllocationInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        vmaCreateImage(allocator, &imageInfo, &imageAllocationInfo, &image, &imageAllocation, nullptr);

        // Copy from the staging buffer to the image
        _manager->transitionImageLayout(image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        VkCommandBuffer commandBuffer = _manager->beginSingleTimeCommands();
        VkBufferImageCopy region = {};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = {
            texWidth,
            texHeight,
            1
        };
        vkCmdCopyBufferToImage(commandBuffer, stagingBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
        _manager->endSingleTimeCommands(commandBuffer);

        // Transition to a shader layout
        _manager->transitionImageLayout(image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        // Cleanup the staging resources
        vmaDestroyBuffer(allocator, stagingBuffer, stagingAllocation);

        // Create the image view
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(_manager->getDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image view!");
        }
    }

    void VkTextureAtlas::cleanup() {
        vkDestroyImageView(_manager->getDevice(), imageView, nullptr);
        vmaDestroyImage(_manager->getAllocator(), image, imageAllocation);
    }
}

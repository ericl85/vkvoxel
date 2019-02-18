#include "VkTextureAtlas.h"

namespace VkVoxel {
    VkTextureAtlas::VkTextureAtlas(std::shared_ptr<VkManager> manager) : TextureAtlas() {
        _manager = manager;
    }

    void VkTextureAtlas::prepareForGPU() {
        VmaAllocator allocator = _manager->getAllocator();
        VkDeviceSize deviceSize = 0;

        for (TextureInfo texture : _textureInfo) {
            deviceSize += texture.texWidth * texture.texHeight * 4;
        }

        // Create one big buffer for staging all the textures
        VkBuffer stagingBuffer;
        VmaAllocation stagingAllocation;
        VkBufferCreateInfo stagingCreateInfo = {};
        stagingCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        stagingCreateInfo.size = deviceSize;
        stagingCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        VmaAllocationCreateInfo stagingAllocInfo = {};
        stagingAllocInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;
        vmaCreateBuffer(allocator, &stagingCreateInfo, &stagingAllocInfo, &stagingBuffer, &stagingAllocation, nullptr);
        char* data;
        vmaMapMemory(allocator, stagingAllocation, (void**)&data);

        // Now copy the images into the staging buffer one at a time
        // Note: Might be better to do this when loading the files and do one big blob copy, but would need to store
        //       a pointer to the first image and then offsets to each additional.
        size_t currentOffset = 0;
        std::vector<VkBufferImageCopy> bufferCopyRegions;
        for (uint32_t layer = 0; layer < _textureInfo.size(); layer++) {
            // Copy the image into the staging buffer
            VkDeviceSize imageSize = _textureInfo[layer].texWidth * _textureInfo[layer].texHeight * 4;
            memcpy(data + currentOffset, _textureInfo[layer].pixels, (size_t)imageSize);

            // While we're at it create a copy region for this texture to use eventually
            VkBufferImageCopy bufferCopyRegion = {};
            bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            bufferCopyRegion.imageSubresource.mipLevel = 0;
            bufferCopyRegion.imageSubresource.baseArrayLayer = layer;
            bufferCopyRegion.imageSubresource.layerCount = 1;
            bufferCopyRegion.imageExtent.width = _textureInfo[layer].texWidth;
            bufferCopyRegion.imageExtent.height = _textureInfo[layer].texHeight;
            bufferCopyRegion.imageExtent.depth = 1;
            bufferCopyRegion.bufferOffset = currentOffset;
            bufferCopyRegions.push_back(bufferCopyRegion);

            currentOffset += (size_t)imageSize;
        }

        vmaUnmapMemory(allocator, stagingAllocation);

        uint32_t layerCount = static_cast<uint32_t>(_textureInfo.size());

        // Create the image
        VkImageCreateInfo imageCreateInfo = {};
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
        imageCreateInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageCreateInfo.extent = { width, height, 1 };
        imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageCreateInfo.arrayLayers = layerCount;

        // Create a blob of memory to copy the staging buffer into
        VmaAllocationCreateInfo imageAllocationInfo = {};
        imageAllocationInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

        if (vmaCreateImage(allocator, &imageCreateInfo, &imageAllocationInfo, &image, &imageAllocation, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image for texture atlas!");
        }

        // Copy into the destination buffer
        _manager->transitionImageLayout(image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, layerCount);
        
        VkCommandBuffer copyCmdBuffer = _manager->beginSingleTimeCommands();
        vkCmdCopyBufferToImage(copyCmdBuffer, stagingBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, bufferCopyRegions.size(), bufferCopyRegions.data());
        _manager->endSingleTimeCommands(copyCmdBuffer);

        // Transition to shader format
        _manager->transitionImageLayout(image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, layerCount);

        // Cleanup the staging resources
        vmaDestroyBuffer(allocator, stagingBuffer, stagingAllocation);

        // Create the image view
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
        viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = layerCount;

        if (vkCreateImageView(_manager->getDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image view for texture atlas!");
        }
    }

    void VkTextureAtlas::cleanup() {
        vkDestroyImageView(_manager->getDevice(), imageView, nullptr);
        vmaDestroyImage(_manager->getAllocator(), image, imageAllocation);
    }
}

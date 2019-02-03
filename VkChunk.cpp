#include "VkChunk.h"

namespace VkVoxel {
    VkChunk::VkChunk(int x, int y, std::shared_ptr<VkManager> manager) : Chunk(x, y) {
        _prepared = false;

        _manager = manager;
    }

    void VkChunk::prepare(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        prepareVertexBuffer(vertices);
        prepareIndexBuffer(indices);

        _prepared = true;
    }

    void VkChunk::prepareVertexBuffer(const std::vector<Vertex>& vertices) {
        VmaAllocator allocator = _manager->getAllocator();
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VkBufferCreateInfo stagingBufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        stagingBufferInfo.size = bufferSize;
        stagingBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

        VmaAllocationCreateInfo stagingAllocInfo = {};
        stagingAllocInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;

        // Create a staging buffer for the vertex buffer
        VmaAllocation stagingAllocation;
        VkBuffer stagingBuffer;
        vmaCreateBuffer(allocator, &stagingBufferInfo, &stagingAllocInfo, &stagingBuffer, &stagingAllocation, nullptr);
        
        void* data;
        vmaMapMemory(allocator, stagingAllocation, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vmaUnmapMemory(allocator, stagingAllocation);

        if (!_prepared) {
            // If we have never prepared this vertex buffer before, do it now.
            VkBufferCreateInfo vertexBufferCreateInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
            vertexBufferCreateInfo.size = bufferSize;
            vertexBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

            VmaAllocationCreateInfo vertexBufferAllocInfo = {};
            stagingAllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
            
            vmaCreateBuffer(allocator, &vertexBufferCreateInfo, &vertexBufferAllocInfo, &vertexBuffer, &vertexAllocation, nullptr);
        }

        VkCommandBuffer copyVertexCmdBuffer = _manager->beginSingleTimeCommands();
        VkBufferCopy copyRegion = {};
        copyRegion.size = bufferSize;
        vkCmdCopyBuffer(copyVertexCmdBuffer, stagingBuffer, vertexBuffer, 1, &copyRegion);
        _manager->endSingleTimeCommands(copyVertexCmdBuffer);

        vmaDestroyBuffer(allocator, stagingBuffer, stagingAllocation);
    }

    void VkChunk::prepareIndexBuffer(const std::vector<uint32_t>& indices) {
        VmaAllocator allocator = _manager->getAllocator();

        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
        VkBufferCreateInfo stagingBufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        stagingBufferInfo.size = bufferSize;
        stagingBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

        VmaAllocationCreateInfo stagingAllocInfo = {};
        stagingAllocInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;

        // Create a staging buffer for the vertex buffer
        VmaAllocation stagingAllocation;
        VkBuffer stagingBuffer;
        vmaCreateBuffer(allocator, &stagingBufferInfo, &stagingAllocInfo, &stagingBuffer, &stagingAllocation, nullptr);

        void* data;
        vmaMapMemory(allocator, stagingAllocation, &data);
        memcpy(data, indices.data(), (size_t)bufferSize);
        vmaUnmapMemory(allocator, stagingAllocation);

        if (!_prepared) {
            // If we have never prepared this vertex buffer before, do it now.
            VkBufferCreateInfo indexBufferCreateInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
            indexBufferCreateInfo.size = bufferSize;
            indexBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

            VmaAllocationCreateInfo indexBufferAllocInfo = {};
            stagingAllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

            vmaCreateBuffer(allocator, &indexBufferCreateInfo, &indexBufferAllocInfo, &indexBuffer, &indexAllocation, nullptr);
        }

        VkCommandBuffer copyIndexBufferCmd = _manager->beginSingleTimeCommands();
        VkBufferCopy copyRegion = {};
        copyRegion.size = bufferSize;
        vkCmdCopyBuffer(copyIndexBufferCmd, stagingBuffer, indexBuffer, 1, &copyRegion);
        _manager->endSingleTimeCommands(copyIndexBufferCmd);

        vmaDestroyBuffer(allocator, stagingBuffer, stagingAllocation);
    }

    void VkChunk::cleanup() {
        VmaAllocator allocator = _manager->getAllocator();
        vmaDestroyBuffer(allocator, indexBuffer, indexAllocation);
        vmaDestroyBuffer(allocator, vertexBuffer, vertexAllocation);

        _prepared = false;
    }
}

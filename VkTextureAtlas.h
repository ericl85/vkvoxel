#ifndef __VK_TEXTURE_ATLAS_H_
#define __VK_TEXTURE_ATLAS_H_

#include "TextureAtlas.h"
#include "VkManager.h"

namespace VkVoxel {
    class VkTextureAtlas : public TextureAtlas {
    public:
        VkTextureAtlas(std::string fileName, std::shared_ptr<VkManager> manager);
        virtual void cleanup();

        VkImage image;
        VkImageView imageView;
        VmaAllocation imageAllocation;

    protected:
        virtual void prepare(uint32_t texWidth, uint32_t texHeight, int texChannels, stbi_uc* pixels);

    private:
        std::shared_ptr<VkManager> _manager;
    };
}

#endif
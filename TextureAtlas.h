#ifndef __TEXTURE_ATLAS_H_
#define __TEXTURE_ATLAS_H_

#include <string>
#include <unordered_map>
#include "stb/stb_image.h"

namespace VkVoxel {
    struct TextureInfo {
        std::string name;
        std::string fileName;
        uint32_t texWidth;
        uint32_t texHeight;
        int texChannels;
        stbi_uc* pixels;
    };

    class TextureAtlas {
    public:
        TextureAtlas();

        void addTexture(std::string name, std::string fileName);
        void prepare();

        uint32_t width = 0;
        uint32_t height = 0;

        virtual void cleanup() = 0;

    private:
        

    protected:
        std::vector<TextureInfo> _textureInfo;
        virtual void prepareForGPU() = 0;
        
    };
}

#endif

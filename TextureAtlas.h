#ifndef __TEXTURE_ATLAS_H_
#define __TEXTURE_ATLAS_H_

#include <string>
#include "stb/stb_image.h"

namespace VkVoxel {
    class TextureAtlas {
    public:
        TextureAtlas(std::string fileName);

        void initialize();
        virtual void cleanup() = 0;

    private:
        std::string _fileName;

    protected:
        virtual void prepare(uint32_t texWidth, uint32_t texHeight, int texChannels, stbi_uc* pixels) = 0;
        
    };
}

#endif

#ifndef __TEXTURE_ATLAS_H_
#define __TEXTURE_ATLAS_H_

#include <string>
#include "stb/stb_image.h"

namespace VkVoxel {
    class TextureAtlas {
    public:
        TextureAtlas(std::string fileName);

        void initialize();

    private:
        std::string _fileName;

    protected:
        virtual void prepare(int texWidth, int texHeight, int texChannels, stbi_uc* pixels) = 0;
        virtual void cleanup() = 0;
    };
}

#endif

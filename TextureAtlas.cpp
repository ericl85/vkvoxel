#include "TextureAtlas.h"

namespace VkVoxel {
    TextureAtlas::TextureAtlas(std::string fileName) {
        _fileName = fileName;
    }

    void TextureAtlas::initialize() {
        int texWidth, texHeight, texChannels;
        stbi_uc* pixels = stbi_load(_fileName.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

        uint32_t memSize = texWidth * texHeight * 4;

        prepare(texWidth, texHeight, texChannels, pixels);

        stbi_image_free(pixels);
    }
}

#include "TextureAtlas.h"

namespace VkVoxel {
    TextureAtlas::TextureAtlas() { }

    void TextureAtlas::addTexture(std::string name, std::string fileName) {
        int texWidth, texHeight, texChannels;
        stbi_uc* pixels = stbi_load(fileName.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

        TextureInfo textureInfo;
        textureInfo.name = name;
        textureInfo.fileName = fileName;
        textureInfo.pixels = pixels;
        textureInfo.texWidth = texWidth;
        textureInfo.texHeight = texHeight;
        textureInfo.texChannels = texChannels;

        if (width == 0 && height == 0) {
            width = texWidth;
            height = texHeight;
        }
        else if (width != texWidth || height != texHeight) {
            throw std::runtime_error("Texture atlas textures must be the same dimensions!");
        }

        _textureInfo.push_back(textureInfo);
    }

    void TextureAtlas::prepare() {
        prepareForGPU();

        for (TextureInfo texture : _textureInfo)
        {
            stbi_image_free(texture.pixels);
            texture.pixels = nullptr;
        }
    }
}


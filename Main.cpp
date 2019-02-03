#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "VkVoxelApplication.h"

int main() {
    VkVoxel::VkVoxelApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

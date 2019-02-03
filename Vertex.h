#ifndef __VERTEX_H_
#define __VERTEX_H_

#include <array>

#include "glm/vec2.hpp"
#include <array>
#include "glm/vec3.hpp"
#include "VkUtil.h"

namespace VkVoxel {
    struct Vertex {
    public:
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription();
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
        
    };
}

#endif
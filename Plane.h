#ifndef __PLANE_H_
#define __PLANE_H_

#include "glm/vec4.hpp"

namespace VkVoxel {
    class Plane {
    public:
        glm::vec4 normal;
        glm::vec4 position;
    };
}

#endif
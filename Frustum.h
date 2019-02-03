#ifndef __FRUSTUM_H_
#define __FRUSTUM_H_

#include "glm/mat4x4.hpp"
#include "Plane.h"

namespace VkVoxel {
    class Frustum {
    public:
        Frustum();
        Frustum(const glm::mat4x4& projection, const glm::mat4x4& view);

        void fromCamera(const glm::mat4x4& projection, const glm::mat4x4& view);

        Plane nearPlan;
        Plane farPlane;
        Plane left;
        Plane right;
        Plane top;
        Plane bottom;
    };
}

#endif

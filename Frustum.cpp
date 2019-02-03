#include "glm/matrix.hpp"
#include "glm/glm.hpp"
#include "Frustum.h"

namespace VkVoxel {
    Frustum::Frustum() { }

    Frustum::Frustum(const glm::mat4x4& projection, const glm::mat4x4& view) {
        fromCamera(projection, view);
    }

    void Frustum::fromCamera(const glm::mat4x4& projection, const glm::mat4x4& view) {
        glm::mat4x4 clipMatrix = projection * view;

        right.position.x = clipMatrix[3][0] - clipMatrix[0][0];
        right.position.y = clipMatrix[3][1] - clipMatrix[0][1];
        right.position.z = clipMatrix[3][2] - clipMatrix[0][2];
        right.position.w = clipMatrix[3][3] - clipMatrix[0][3];
        right.position = glm::normalize(right.position);

        left.position.x = clipMatrix[3][0] + clipMatrix[0][0];
        left.position.y = clipMatrix[3][1] + clipMatrix[0][1];
        left.position.z = clipMatrix[3][2] + clipMatrix[0][2];
        left.position.w = clipMatrix[3][3] + clipMatrix[0][3];
        left.position = glm::normalize(left.position);

        bottom.position.x = clipMatrix[3][0] + clipMatrix[1][0];
        bottom.position.y = clipMatrix[3][1] + clipMatrix[1][1];
        bottom.position.z = clipMatrix[3][2] + clipMatrix[1][2];
        bottom.position.w = clipMatrix[3][3] + clipMatrix[1][3];
        bottom.position = glm::normalize(bottom.position);

        top.position.x = clipMatrix[3][0] - clipMatrix[1][0];
        top.position.y = clipMatrix[3][1] - clipMatrix[1][1];
        top.position.z = clipMatrix[3][2] - clipMatrix[1][2];
        top.position.w = clipMatrix[3][3] - clipMatrix[1][3];
        top.position = glm::normalize(top.position);

        nearPlan.position.x = clipMatrix[3][0] - clipMatrix[2][0];
        nearPlan.position.y = clipMatrix[3][1] - clipMatrix[2][1];
        nearPlan.position.z = clipMatrix[3][2] - clipMatrix[2][2];
        nearPlan.position.w = clipMatrix[3][3] - clipMatrix[2][2];
        nearPlan.position = glm::normalize(nearPlan.position);

        farPlane.position.x = clipMatrix[3][0] + clipMatrix[2][0];
        farPlane.position.y = clipMatrix[3][1] + clipMatrix[2][1];
        farPlane.position.z = clipMatrix[3][2] + clipMatrix[2][2];
        farPlane.position.w = clipMatrix[3][3] + clipMatrix[2][3];
        farPlane.position = glm::normalize(farPlane.position);
    }
}

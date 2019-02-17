#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "Frustum.h"

namespace VkVoxel {
    class Camera {
    public:
        Camera(uint32_t resWidth, uint32_t resHeight);
        
        void rebuildProjection(uint32_t resWidth, uint32_t resHeight);
        glm::mat4x4 getProjection();
        glm::mat4x4 getView();
        
        void setPosition(const glm::vec3& position);
        glm::vec3 getPosition();
        glm::vec3 getFront();

        void setRotation(float pitch, float yaw);
        float getPitch();
        float getYaw();

        void move(glm::vec3 direction, float amount);

        Frustum getFrustum();
    private:
        // Our view and projection matrix
        glm::mat4x4 _projection;
        glm::mat4x4 _view;

        // Our FPS camera state.
        glm::vec3 _position;
        glm::vec3 _front;
        float _pitch;
        float _yaw;

        // Our cameras frustum
        Frustum _frustum;

        void updateCamera();
    };
};

#endif

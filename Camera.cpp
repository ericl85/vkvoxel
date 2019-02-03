#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

namespace VkVoxel {
    Camera::Camera(uint32_t resWidth, uint32_t resHeight) {
        _position = glm::vec3(0.0f, 1.0f, 0.0f);
        _front = glm::vec3(0.0f, 1.0f, 1.0f);

        _projection = glm::infinitePerspective(glm::radians(45.0f), resWidth / (float)resHeight, 0.1f);
        //_projection = glm::perspective(glm::radians(45.0f), resWidth / (float)resHeight, 0.1f, 10.0f);
        _view = glm::lookAt(_position, _front, glm::vec3(0.0f, 1.0f, 0.0f));

        _yaw = 0.0f;
        _pitch = 0.0f;

        // Update our camera frustum
        _frustum.fromCamera(_projection, _view);
    }

    glm::mat4x4 Camera::getProjection() {
        return _projection;
    }

    glm::mat4x4 Camera::getView() {
        return _view;
    }

    void Camera::setPosition(const glm::vec3& position) {
        glm::vec3 delta = _position - position;
        _position = position;

        _front = _front + delta;

        updateCamera();
    }

    glm::vec3 Camera::getPosition() {
        return _position;
    }

    void Camera::move(glm::vec3 direction, float amount) {
        _position = _position + (direction * amount);
        _front = _front + (direction * amount);
        updateCamera();
    }

    float Camera::getPitch() {
        return _pitch;
    }

    float Camera::getYaw() {
        return _yaw;
    }

    void Camera::setRotation(float pitch, float yaw) {
        _pitch = pitch;
        _yaw = yaw;

        updateCamera();
    }

    Frustum Camera::getFrustum() {
        return _frustum;
    }

    void Camera::updateCamera() {
        /*float cosPitch = cos(_pitch);
        float sinPitch = sin(_pitch);
        float cosYaw = cos(_yaw);
        float sinYaw = sin(_yaw);

        glm::vec3 xAxis = glm::vec3(cosYaw, 0, -sinYaw);
        glm::vec3 yAxis = glm::vec3(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
        glm::vec3 zAxis = glm::vec3(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

        _view[0] = { xAxis.x, yAxis.x, zAxis.x, 0 };
        _view[1] = { xAxis.y, yAxis.y, zAxis.y, 0 };
        _view[2] = { xAxis.z, yAxis.z, zAxis.z, 0 };
        _view[3] = { -glm::dot(xAxis, _position), -glm::dot(yAxis, _position), -glm::dot(zAxis, _position), 1 };*/
        
        _view = glm::lookAt(_position, _front, glm::vec3(0.0f, 1.0f, 0.0f));

        _frustum.fromCamera(_projection, _view);
    }
}

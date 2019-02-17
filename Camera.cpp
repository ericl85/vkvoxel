#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

namespace VkVoxel {
    Camera::Camera(uint32_t resWidth, uint32_t resHeight) {
        _position = glm::vec3(0.0f, 1.0f, 0.0f);
        _front = glm::vec3(0.0f, 1.0f, 1.0f);

        //_projection = glm::infinitePerspective(glm::radians(45.0f), resWidth / (float)resHeight, 0.1f);
        _projection = glm::perspective(glm::radians(45.0f), resWidth / (float)resHeight, 0.1f, 1000.0f);
        _view = glm::lookAt(_position, _position + _front, glm::vec3(0.0f, 1.0f, 0.0f));

        _yaw = 0.0f;
        _pitch = 0.0f;

        // Update our camera frustum
        _frustum.fromCamera(_projection, _view);
    }

    void Camera::rebuildProjection(uint32_t resWidth, uint32_t resHeight) {
        _projection = glm::perspective(glm::radians(45.0f), resWidth / (float)resHeight, 0.1f, 1000.0f);
    }

    glm::mat4x4 Camera::getProjection() {
        return _projection;
    }

    glm::mat4x4 Camera::getView() {
        return _view;
    }

    void Camera::setPosition(const glm::vec3& position) {
        _position = position;

        updateCamera();
    }

    glm::vec3 Camera::getPosition() {
        return _position;
    }

    void Camera::move(glm::vec3 direction, float amount) {
        _position = _position + (direction * amount);

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

    glm::vec3 Camera::getFront() {
        return _front;
    }

    Frustum Camera::getFrustum() {
        return _frustum;
    }

    void Camera::updateCamera() {
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(front);

        _view = glm::lookAt(_position, _position + _front, glm::vec3(0.0f, 1.0f, 0.0f));

        _frustum.fromCamera(_projection, _view);
    }
}

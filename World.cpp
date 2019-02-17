#include "World.h"

namespace VkVoxel {
    void World::initialize(std::shared_ptr<Renderer> renderer, std::shared_ptr<Camera> camera) {
        _camera = camera;
        
        _renderer = renderer;
        _renderer->setCamera(_camera);

        _chunks.resize(2);

        _chunks[0] = _renderer->createChunk(0, 0);
        _chunks[1] = _renderer->createChunk(1, 1);

        // Temporary: Generate a ground
        for (int xBlock = 0; xBlock < CHUNK_SIZE; xBlock++) {
            for (int zBlock = 0; zBlock < CHUNK_SIZE; zBlock++) {
                _chunks[0]->blocks[0][xBlock][zBlock] = 1;
                _chunks[1]->blocks[0][xBlock][zBlock] = 3;
            }
        }

        _chunks[0]->blocks[1][8][8] = 2;

        _renderer->setChunks(_chunks);

        _lastTime = std::chrono::high_resolution_clock::now();
    }

    void World::update(InputState inputState) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float tickTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - _lastTime).count();

        glm::vec3 cameraPos = _camera->getPosition();
        glm::vec3 cameraFront = _camera->getFront();
        float yaw = _camera->getYaw();
        float pitch = _camera->getPitch();

        float cameraSpeed = 0.001f;

        // Update the camera position
        cameraPos += (cameraFront * tickTime * (inputState.forwardSpeed - inputState.backwardSpeed) * cameraSpeed);
        cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * tickTime * (inputState.rightSpeed - inputState.leftSpeed) * cameraSpeed;

        // Update the camera rotation
        yaw += inputState.yawSpeed;
        pitch += inputState.pitchSpeed;
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        _camera->setPosition(cameraPos);
        _camera->setRotation(pitch, yaw);
    }

    void World::render() {
        _renderer->render();
    }

    
}

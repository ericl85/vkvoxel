#ifndef __INPUT_STATE_H_
#define __INPUT_STATE_H_

#include <algorithm>

namespace VkVoxel {
    class InputState {
    public:
        float forwardSpeed = 0.0f;
        float backwardSpeed = 0.0f;
        float leftSpeed = 0.0f;
        float rightSpeed = 0.0f;

        float pitchSpeed = 0.0f;
        float yawSpeed = 0.0f;

        bool jump = false;
        bool trigger = false;
        bool activate = false;
        bool menu = false;
    };
}

#endif

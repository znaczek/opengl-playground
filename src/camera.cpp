//
// Created by znaczek on 10.04.2022.
//

#include <iostream>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "camera.h"
#include "constants.h"

float r = 25;
float ro = glm::sqrt(0 + 0 + r*r);

struct SCREEN_SIZE {
    float x;
    float y;
};

SCREEN_SIZE screenSize = {
        1,
        1
};

glm::mat4 Camera::getV() {
    if (this->top.x == 0 && this->top.y == 0 && this->top.z == 0) {
        this->top = glm::vec3(0, 1, 0);
    }
    if (this->eye.x == 0 && this->eye.y == 0 && this->eye.z == 0) {
        this->eye.z = -r;
    }
    return glm::lookAt(this->eye, glm::vec3(0, 0, 0), this->top);
}

glm::mat4 Camera::getP() {
    return glm::perspective(glm::radians(50.0f), screenSize.x / screenSize.y, 0.1f, 100.0f);
}

glm::vec3 Camera::getEye() {
    return this->eye;
}

void Camera::rotate(double dx, double dy) {
    float yaw = 2*PI / WINDOW_WIDTH * dx;
    float pitch = 2*PI / WINDOW_HEIGHT * dy;

    float currentYaw;
    if (this->eye.z == 0) {
        if (this->eye.x > 0) {
            currentYaw = PI/2;
        } else {
            currentYaw = -PI/2;
        }
    } else {
        currentYaw = glm::atan(this->eye.x / -this->eye.z);
        if (this->eye.z > 0) {
            currentYaw = currentYaw + PI;
        }
    }

    float currentPitch = glm::asin(this->eye.y / ro);

    float newYaw = currentYaw + yaw;
    float newPitch = glm::clamp(currentPitch + pitch, -PI/2, PI/2);

    glm::vec3 newEye = glm::vec3(
            ro * glm::sin(newYaw) * glm::cos(newPitch),
            ro * glm::sin(newPitch),
            -ro * glm::cos(newYaw) * glm::cos(newPitch)
    );

    this->eye.x = newEye.x;
    this->eye.y = newEye.y;
    this->eye.z = newEye.z;

}

Camera &Camera::instance() {
    static Camera instance_;
    return instance_;
}

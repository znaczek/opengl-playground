//
// Created by znaczek on 10.04.2022.
//

#ifndef TETRIS_CAMERA_H
#define TETRIS_CAMERA_H

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    static Camera& instance();
    glm::mat4 getV();
    glm::mat4 getP();
    glm::vec3 getEye();
    void rotate(double dx, double dy);
private:
    glm::vec3 eye;
    glm::vec3 top;
};


#endif //TETRIS_CAMERA_H

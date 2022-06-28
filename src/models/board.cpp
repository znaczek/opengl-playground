//
// Created by znaczek on 02.04.2022.
//
#include <GL/glew.h>
#include "board.h"
#include "cuboidGenerator.h"

const int blocks = 8;

Board::Board() {
    asset = {
            getShaderProgram(),
            0,
            0,
            GL_TRIANGLES,
            0,
            verticesPerBlock * blocks
    };
    glm::mat4 model = glm::mat4(1.0f);
    setTransform(model);

    float length = 10;
    float width = 0.1;
    float offset = length/2;
    glm::vec3 color = {0,0,0};
    generateCuboid(vertexData, color, 0                 , width, width, length,-offset, 0,-offset);
    generateCuboid(vertexData, color, pointsPerBlock * 1, width, width, length,-offset, 0, offset);
    generateCuboid(vertexData, color, pointsPerBlock * 2, width, width, length, offset, 0,-offset);
    generateCuboid(vertexData, color, pointsPerBlock * 3, width, width, length, offset, 0, offset);

    generateCuboid(vertexData, color, pointsPerBlock * 4, length, width, width, 0, -offset, -offset);
    generateCuboid(vertexData, color, pointsPerBlock * 5, length, width, width, 0, -offset, offset);
    generateCuboid(vertexData, color, pointsPerBlock * 6, width, length, width, -offset, -offset, 0);
    generateCuboid(vertexData, color, pointsPerBlock * 7, width, length, width, offset, -offset, 0);

    this->_init();
}

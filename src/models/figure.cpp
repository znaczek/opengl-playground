//
// Created by znaczek on 02.04.2022.
//
#include <GL/glew.h>
#include "glm/gtc/type_ptr.hpp"
#include "cuboidGenerator.h"
#include "figure.h"
#include <cstdarg>
#include <vector>
#include <random>

Figure::Figure(glm::vec3 color, glm::vec3 position, int blocksCount, ...) {
    asset = {
            getShaderProgram(),
            (GLuint) rand(),
            (GLuint) rand(),
            GL_TRIANGLES,
            0,
            verticesPerBlock * blocksCount
    };

    this->color = color;

    va_list vl;
    va_start(vl, blocksCount);
    this->blocks = std::vector<glm::vec3>();
    for (int i = 0; i < blocksCount; i++) {
        this->blocks.push_back(va_arg(vl, glm::vec3));
    }
    va_end(vl);

    this->position = this->fixPosition(position);
    setTransform(glm::translate(glm::mat4(1.0f), this->position));

    float width = 1;

    for (int i = 0; i < blocksCount; i++) {
        glm::vec3 currentBlock = blocks.at(i);
        generateCuboid(vertexData, color, pointsPerBlock * i, width, width, width, currentBlock.x, currentBlock.y,
                       currentBlock.z);
    }

    this->_init();
}

glm::vec3 Figure::fixPosition(glm::vec3 position) {
    return glm::vec3(position.x - 0.5, position.y - 4.5, position.z - 0.5);
}

glm::vec3 Figure::defixPosition(glm::vec3 position) {
    return glm::vec3(position.x, position.y + 5.5, position.z);
}

void Figure::move(glm::vec3 diff) {
    this->position += diff;
    setTransform(glm::translate(glm::mat4(1.0f), this->position));
}

std::vector<CBlock> Figure::getBlocks() {
    std::vector<CBlock> blcks;
    for (auto block: this->blocks) {
        blcks.push_back({
                                 block + this->defixPosition(this->position),
                                 this->color
                         });
    }
    return blcks;
}

glm::vec3 Figure::getPosition() {
    return this->defixPosition(this->position);
}

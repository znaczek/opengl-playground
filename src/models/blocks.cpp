//
// Created by znaczek on 02.04.2022.
//
#include <GL/glew.h>
#include "blocks.h"
#include "cuboidGenerator.h"

Blocks::Blocks(std::vector<CBlock> blocks) {
    int blocksCount = blocks.size();
    glm::vec3 color = blocksCount > 0 ? blocks.at(0).color : glm::vec3();
    asset = {
            getShaderProgram(),
            0,
            0,
            GL_TRIANGLES,
            0,
            verticesPerBlock * blocksCount
    };
    glm::mat4 model = glm::mat4(1.0f);
    setTransform(model);

    float width = 1;

    for (int i = 0; i < blocksCount; i++) {
        glm::vec3 currentBlock = this->fixPosition(blocks.at(i).block);
        generateCuboid(vertexData, blocks.at(i).color, pointsPerBlock * i, width, width, width, currentBlock.x, currentBlock.y, currentBlock.z);
    }

    this->_init();
}

glm::vec3 Blocks::fixPosition(glm::vec3 position) {
    return glm::vec3(position.x, position.y - 5.5, position.z);
}

//
// Created by znaczek on 02.04.2022.
//

#ifndef TETRIS_BLOCKS_H
#define TETRIS_BLOCKS_H

#include <GL/glew.h>
#include "model.h"
#include "glm/glm.hpp"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

class Blocks : public Model {
public:
    explicit Blocks(std::vector<CBlock> blocks);
    glm::vec3 fixPosition(glm::vec3);
};


#endif //TETRIS_BLOCKS_H

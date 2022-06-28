//
// Created by znaczek on 22.05.22.
//

#ifndef TETRIS_FIGURE_H
#define TETRIS_FIGURE_H

#include <GL/glew.h>
#include "model.h"
#include "model_asset.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "cuboidGenerator.h"

class Figure: public Model {
public:
    explicit Figure(glm::vec3 color, glm::vec3 position, int n, ...);
    void move(glm::vec3 position);
    std::vector<CBlock> getBlocks();
    glm::vec3 getPosition();
private:
    glm::vec3 position;
    glm::vec3 fixPosition(glm::vec3);
    glm::vec3 defixPosition(glm::vec3);
    glm::vec3 color;
    std::vector<glm::vec3> blocks;
};

#endif //TETRIS_FIGURE_H

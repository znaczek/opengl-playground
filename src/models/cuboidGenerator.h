//
// Created by znaczek on 22.05.22.
//

#ifndef TETRIS_CUBOIDGENERATOR_H
#define TETRIS_CUBOIDGENERATOR_H

#include <GL/glew.h>
#include <vector>
#include "glm/glm.hpp"

const int vertexPointPerVertex = 3;
const int normalPointsPerVertex = 3;
const int colorPointsPerVertex = 3;
const int pointsPerVertex = vertexPointPerVertex + normalPointsPerVertex + colorPointsPerVertex;
const int verticesPerFace = 6;
const int facesPerBlock = 6;
const int verticesPerBlock = facesPerBlock * verticesPerFace;
const int pointsPerBlock = verticesPerBlock * pointsPerVertex;

void generateCuboid(GLfloat* arr, glm::vec3 color, int offset, float w, float l, float h, float dw, float dh, float dl);


#endif //TETRIS_CUBOIDGENERATOR_H

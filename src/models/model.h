#ifndef TETRIS_MODEL_H
#define TETRIS_MODEL_H

#include "model_asset.h"
#include "src/shaderprogram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "cuboidGenerator.h"

struct CBlock {
    glm::vec3 block;
    glm::vec3 color;
};

class Model {
public:
    Model();
    void draw();
    void setTransform(glm::mat4 transform);
protected:
    ModelAsset asset;
    glm::mat4 _transform;
    GLfloat vertexData[pointsPerBlock * 1000] = {0};
    ShaderProgram* getShaderProgram();
    void _init();
};


#endif //TETRIS_MODEL_H

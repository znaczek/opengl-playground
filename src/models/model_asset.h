//
// Created by znaczek on 02.04.2022.
//

#ifndef TETRIS_MODEL_ASSET_H
#define TETRIS_MODEL_ASSET_H


#include "../shaderprogram.h"

struct ModelAsset {
    ShaderProgram* shaders;
    // TODO add texture
    GLuint vbo;
    GLuint vao;
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;
};


#endif //TETRIS_MODEL_ASSET_H

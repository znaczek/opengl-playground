#include <GL/glew.h>
#include "model.h"
#include "src/camera.h"

Model::Model() {
}

ShaderProgram* Model::getShaderProgram() {
    return new ShaderProgram("../src/sh_v.glsl", nullptr, "../src/sh_f.glsl");
}

void Model::draw() {
    asset.shaders->use();

    // set uniforms
    glUniformMatrix4fv(asset.shaders->u("P"), 1, false, glm::value_ptr(Camera::instance().getP()));
    glUniformMatrix4fv(asset.shaders->u("V"), 1, false, glm::value_ptr(Camera::instance().getV()));
    glUniformMatrix4fv(asset.shaders->u("M"), 1, false, glm::value_ptr(this->_transform));
    glm::vec3 e = Camera::instance().getEye();

    glUniform3fv(asset.shaders->u("eye"), 1, glm::value_ptr(e));

    //bind VAO and draw
    glBindVertexArray(asset.vao);
    glDrawArrays(asset.drawType, asset.drawStart, asset.drawCount);

    //unbind everything
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    asset.shaders->stopUsing();
}

void Model::_init() {
    glGenBuffers(1, &asset.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, asset.vbo);

    glGenVertexArrays(1, &asset.vao);
    glBindVertexArray(asset.vao);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(asset.shaders->a("vert"));
    glVertexAttribPointer(asset.shaders->a("vert"), 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), NULL);

    glEnableVertexAttribArray(asset.shaders->a("normal"));
    glVertexAttribPointer(asset.shaders->a("normal"), 3, GL_FLOAT, GL_TRUE, 9 * sizeof(GLfloat),
                          (const GLvoid *) (3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(asset.shaders->a("color"));
    glVertexAttribPointer(asset.shaders->a("color"), 3, GL_FLOAT, GL_TRUE, 9 * sizeof(GLfloat),
                          (const GLvoid *) (6 * sizeof(GLfloat)));

    // unbind the VAO
    glBindVertexArray(0);
}

void Model::setTransform(glm::mat4 transform) {
    this->_transform = transform;
}


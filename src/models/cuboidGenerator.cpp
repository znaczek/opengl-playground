//
// Created by znaczek on 22.05.22.
//

#include "cuboidGenerator.h"
#include <GL/glew.h>

void generateCuboid(GLfloat* arr, glm::vec3 color, int offset, float w, float l, float h, float dw, float dh, float dl) {

    w = w/2;
    l = l/2;
    h = h/2;
    GLfloat src[] = {
            //  X     Y     Z           normal              color
            // bottom
            -w + dw,-h + dh,-l + dl,    0.0f, -1.0f, 0.0f,  color.x, color.y, color.z,
            w + dw,-h + dh,-l + dl,     0.0f, -1.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw,-h + dh, l + dl,    0.0f, -1.0f, 0.0f,  color.x, color.y, color.z,
            w + dw,-h + dh,-l + dl,     0.0f, -1.0f, 0.0f,  color.x, color.y, color.z,
            w + dw,-h + dh, l + dl,     0.0f, -1.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw,-h + dh, l + dl,    0.0f, -1.0f, 0.0f,  color.x, color.y, color.z,

            // top
            -w + dw, h + dh,-l + dl,   0.0f, 1.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw, h + dh, l + dl,   0.0f, 1.0f, 0.0f,  color.x, color.y, color.z,
            w + dw, h + dh,-l + dl,    0.0f, 1.0f, 0.0f,  color.x, color.y, color.z,
            w + dw, h + dh,-l + dl,    0.0f, 1.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw, h + dh, l + dl,   0.0f, 1.0f, 0.0f,  color.x, color.y, color.z,
            w + dw, h + dh, l + dl,    0.0f, 1.0f, 0.0f,  color.x, color.y, color.z,

            // back
            -w + dw,-h + dh, l + dl,   0.0f, 0.0f, 1.0f,  color.x, color.y, color.z,
            w + dw,-h + dh, l + dl,    0.0f, 0.0f, 1.0f,  color.x, color.y, color.z,
            -w + dw, h + dh, l + dl,   0.0f, 0.0f, 1.0f,  color.x, color.y, color.z,
            w + dw,-h + dh, l + dl,    0.0f, 0.0f, 1.0f,  color.x, color.y, color.z,
            w + dw, h + dh, l + dl,    0.0f, 0.0f, 1.0f,  color.x, color.y, color.z,
            -w + dw, h + dh, l + dl,   0.0f, 0.0f, 1.0f,  color.x, color.y, color.z,

            // front
            -w + dw,-h + dh,-l + dl,   0.0f, 0.0f, -1.0f,  color.x, color.y, color.z,
            -w + dw, h + dh,-l + dl,   0.0f, 0.0f, -1.0f,  color.x, color.y, color.z,
            w + dw,-h + dh,-l + dl,    0.0f, 0.0f, -1.0f,  color.x, color.y, color.z,
            w + dw,-h + dh,-l + dl,    0.0f, 0.0f, -1.0f,  color.x, color.y, color.z,
            -w + dw, h + dh,-l + dl,   0.0f, 0.0f, -1.0f,  color.x, color.y, color.z,
            w + dw, h + dh,-l + dl,    0.0f, 0.0f, -1.0f,  color.x, color.y, color.z,

            // left
            -w + dw,-h + dh, l + dl,   -1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw, h + dh,-l + dl,   -1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw,-h + dh,-l + dl,   -1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw,-h + dh, l + dl,   -1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw, h + dh, l + dl,   -1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            -w + dw, h + dh,-l + dl,   -1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,

            // right
            w + dw,-h + dh, l + dl,  1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            w + dw,-h + dh,-l + dl,  1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            w + dw, h + dh,-l + dl,  1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            w + dw,-h + dh, l + dl,  1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            w + dw, h + dh,-l + dl,  1.0f, 0.0f, 0.0f,  color.x, color.y, color.z,
            w + dw, h + dh, l + dl,  1.0f, 0.0f, 0.0f,  color.x, color.y, color.z
    };

    for (int i = 0; i < pointsPerBlock; ++i) {
        arr[i + offset] = src[i];
    }
}
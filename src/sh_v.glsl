# version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 eye;

in vec3 vert;
in vec3 normal;
in vec3 color;

out vec3 fragVert;
out vec3 fragNormal;
out vec3 fragColor;

void main() {
    fragNormal = normal;
    fragVert = vert;
    fragColor = color;

    gl_Position = P * V * M * vec4(vert, 1);
}


# version 330

out vec4 pixelColor;

uniform vec3 lightPosition=vec3(0,0,0);
uniform vec3 lightColor=vec3(1,1,1);
uniform mat4 V;
uniform mat4 P;
uniform mat4 M;
uniform vec3 eye;

in vec3 fragNormal;
in vec3 fragVert;
in vec3 fragColor;

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(M)));
    vec3 normal = normalize(normalMatrix * fragNormal);

    vec3 vertex = vec3(M * vec4(fragVert, 1));

    vec3 surfaceToLight = eye - vertex;

    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0.1, 1);

    vec4 surfaceColor = vec4(fragColor.x, fragColor.y, fragColor.z, 1);
    pixelColor = vec4(brightness * lightColor * surfaceColor.rgb, surfaceColor.a);
}



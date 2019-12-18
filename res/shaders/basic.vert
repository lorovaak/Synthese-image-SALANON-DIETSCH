#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aPositionCube;

uniform mat4 uViewProj;

void main() {
    gl_Position = uViewProj * vec4(aPos+aPositionCube, 1.0);
}

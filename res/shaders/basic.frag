#version 330 core
out vec4 fragColor;

in vec4 vColorCube;

void main() {
    fragColor = vColorCube;
}

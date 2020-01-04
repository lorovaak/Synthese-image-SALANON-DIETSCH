#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aPositionCube;
layout (location = 3) in vec4 aColorCube;


out vec4 vColorCube;
out vec3 fragPos;
out vec3 Normal;

uniform mat4 uViewProj;

void main() {
    gl_Position = uViewProj * vec4(aPos+aPositionCube, 1.0);
	fragPos = vec3(vec4(aPos, 1.0));
	vColorCube = aColorCube;
	Normal = aNormal;
}

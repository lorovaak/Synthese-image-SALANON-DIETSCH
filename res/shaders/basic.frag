#version 330 core

in vec4 vColorCube;

out vec4 fragColor;

uniform vec4 uLightColor;

void main() {

    // float ambientStrength = 0.3;
    // vec4 ambient = vec4(vec3(uLightColor), 1.0);
    vec4 lightResult = uLightColor * vColorCube;
    fragColor = lightResult;

    //fragColor = vColorCube;
}

#version 330 core

in vec4 vColorCube;
in vec3 Normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec4 uLightColor;
uniform vec3 uLightPos;  

void main() {

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - fragPos); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * uLightColor;

    vec4 lightResult = (uLightColor + diffuse) * vColorCube;
    fragColor = lightResult;
}

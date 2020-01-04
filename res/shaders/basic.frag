#version 330 core

in vec4 vColorCube;
in vec3 Normal;
in vec3 fragPos;

out vec4 fragColor;
//out vec3 Normal;

uniform vec4 uLightColor;
uniform vec3 uLightPos;  

void main() {

    //vec4 lightResult = uLightColor * vColorCube;
    //fragColor = lightResult;
    
    //Normal = aNormal;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - fragPos); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * uLightColor;

    vec4 lightResult = (uLightColor + diffuse) * vColorCube;
    fragColor = lightResult;
}

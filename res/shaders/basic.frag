#version 330 core

in vec4 vColorCube;
in vec3 Normal;
in vec3 fragPos;
in vec3 posInWorld;

out vec4 fragColor;

uniform vec4 uLightColor;
uniform vec3 uLightPos;  

void main() {

	vec3 ambient = vec3(0.45);

    vec3 norm = normalize(Normal);
	float dist = length(uLightPos - posInWorld);
    vec3 lightDir = (uLightPos - posInWorld)/dist; 
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * uLightColor;

	vec3 lightIntensity = min(ambient + 3500 * uLightColor.rgb * diffuse.rgb / (dist*dist), 1);
    vec3 lightResult =  lightIntensity * vColorCube.rgb ;
    fragColor = vec4(lightResult, vColorCube.a);
}

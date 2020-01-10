#version 330 core

in vec4 vColorCube;
in vec3 Normal;
in vec3 fragPos;
in vec3 posInWorld;

out vec4 fragColor;

uniform vec4 uLightColor;
uniform vec3 uLightPos;  
uniform vec3 uLightDir;  

void main() {

	vec3 ambient = vec3(0.45);
	vec4 diffusePoint;
	vec4 diffuseDir;
    vec3 norm = normalize(Normal);
	float dist = length(uLightPos - posInWorld);
	vec3 lightDir = (uLightPos - posInWorld)/dist; 

	{
		float diff = max(dot(norm, lightDir), 0.0);
		diffusePoint = diff * uLightColor;
	}

	{
		float diff = max(dot(norm, uLightDir), 0.0);
		diffuseDir = diff * uLightColor;
	}

	vec3 lightIntensity = min(ambient + uLightColor.rgb * diffuseDir.rgb + 3500 * uLightColor.rgb * diffusePoint.rgb / (dist*dist), 1);
    vec3 lightResult =  lightIntensity * vColorCube.rgb ;
    fragColor = vec4(lightResult, vColorCube.a);
}

#pragma once

#include <glm/glm.hpp>
#include "TrackballCamera.hpp"
#include "shader.h"
#include <vector>
#include <glad/glad.h>

class CubesExistants {
public:
    CubesExistants();
    ~CubesExistants();
	void draw(const glimac::TrackballCamera& cam, const glm::vec4 &lightEffect);
	void creerUnCube(const glm::vec3& coordonees, const glm::vec4& couleurs);
	void deplacerCube(glm::vec3& positionActuelle, glm::vec3& nouvellePosition);
	void supprimerCube(glm::vec3& position);
	int indiceCube(const glm::vec3& position);
	void updateGPU();
	void changeCouleur(const glm::vec3& cubePosition, const glm::vec4& nouvelleCouleur);
	void extrusion(glm::vec3 cubePosition, const glm::vec4& couleurCube);
	void creuser(glm::vec3 cubePosition, const glm::vec4& couleurCube);

public:
	std::vector<glm::vec3> positionCubesExistants;
	std::vector<glm::vec4> couleursCubesExistants;
	glm::vec4 lightEffect;

private:
    unsigned int m_vao;
    unsigned int m_ib;
    Shader m_shader;
	GLuint vbPositionsCubesID;
	GLuint vbCouleursCubesID;
};

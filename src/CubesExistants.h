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
	void draw(const glimac::TrackballCamera& cam);
	void CubesExistants::creerUnCube(const glm::vec3& coordonees, const glm::vec4& couleurs);
	void CubesExistants::deplacerCube(glm::vec3& positionActuelle, glm::vec3& nouvellePosition);
	void CubesExistants::supprimerCube(glm::vec3& position);
	int CubesExistants::indiceCube(const glm::vec3& position);
	void updateGPU();
	void CubesExistants::changeCouleur(const glm::vec3& cubePosition, const glm::vec4& nouvelleCouleur);
	void CubesExistants::extrusion(glm::vec3 cubePosition, const glm::vec4& couleurCube);
	void CubesExistants::creuser(glm::vec3 cubePosition, const glm::vec4& couleurCube);

public:
	std::vector<glm::vec3> positionCubesExistants;
	std::vector<glm::vec4> couleursCubesExistants;

private:
    unsigned int m_vao;
    unsigned int m_ib;
    Shader m_shader;
	GLuint vbPositionsCubesID;
	GLuint vbCouleursCubesID;
};

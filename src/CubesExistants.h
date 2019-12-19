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
	void creerUnCube(glm::vec3 coordonees, glm::vec4 couleurs);
	void déplacerCube(glm::vec3 positionActuelle, glm::vec3 nouvellePosition);
	void supprimerCube(const glm::vec3 position);
	int indiceCube(const glm::vec3 position);
	void updateGPU();

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

#pragma once

#include <glm/glm.hpp>
#include "TrackballCamera.hpp"
#include "shader.h"
#include <vector>
#include <glad/glad.h>
#include "CubesExistants.h"

class Curseur {
	public:
		Curseur();
		~Curseur();

	public:
		CubesExistants cubeCurseur;

	private:
		glm::vec3 curseurPosition;
		glm::vec4 curseurCouleur;

};
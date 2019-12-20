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
		void move_x(int i);
		void move_y(int i);
		void move_z(int i);
		void draw(const glimac::TrackballCamera& cam);

	public:
		CubesExistants cubeCurseur;
		glm::vec3 curseurPosition;
		glm::vec4 curseurCouleur;

};
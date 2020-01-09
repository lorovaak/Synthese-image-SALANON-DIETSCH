#include "Curseur.h"
#include <iostream>
#include "gl-exception.h"

#include <glm/gtc/matrix_transform.hpp>

Curseur::Curseur()
	: curseurPosition(glm::vec3 (0,0,0)), curseurCouleur(0,0,1,1)
{
	cubeCurseur.creerUnCube(curseurPosition, curseurCouleur);
}

Curseur::~Curseur()
{
}

void Curseur::move_x(const int i)
{
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.x += i;
	cubeCurseur.deplacerCube(anciennePosition, curseurPosition);
}

void Curseur::move_y(const int i)
{
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.y += i;
	cubeCurseur.deplacerCube(anciennePosition, curseurPosition);

}

void Curseur::move_z(const int i)
{	
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.z += i;
	cubeCurseur.deplacerCube(anciennePosition, curseurPosition);
}

void Curseur::draw(const glimac::TrackballCamera& cam, const glm::vec4 curseurColor) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	cubeCurseur.draw(cam, curseurColor);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

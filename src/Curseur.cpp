#include "Curseur.h"
#include <iostream>


Curseur::Curseur()
	: curseurPosition(glm::vec3 (0,0,0)), curseurCouleur(0,0,1,1)
{
	cubeCurseur.creerUnCube(curseurPosition, curseurCouleur);
}

Curseur::~Curseur()
{
}

void Curseur::move_x(int i)
{
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.x += i;
	cubeCurseur.déplacerCube(anciennePosition, curseurPosition);
}

void Curseur::move_y(int i)
{
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.y += i;
	cubeCurseur.déplacerCube(anciennePosition, curseurPosition);
}

void Curseur::move_z(int i)
{	
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.z += i;
	cubeCurseur.déplacerCube(anciennePosition, curseurPosition);
}
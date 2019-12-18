#include "Curseur.h"

Curseur::Curseur()
	: curseurPosition(glm::vec3 (0,0,0)), curseurCouleur(0,0,1,1)
{
	cubeCurseur.creerUnCube(curseurPosition, curseurCouleur);
}

Curseur::~Curseur()
{
}
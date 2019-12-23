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

void Curseur::move_x(int i)
{
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.x += i;
	cubeCurseur.deplacerCube(anciennePosition, curseurPosition);
}

void Curseur::move_y(int i)
{
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.y += i;
	cubeCurseur.deplacerCube(anciennePosition, curseurPosition);

	//test
	std::cout << curseurPosition.y << std::endl;
}

void Curseur::move_z(int i)
{	
	glm::vec3 anciennePosition = curseurPosition;
	curseurPosition.z += i;
	cubeCurseur.deplacerCube(anciennePosition, curseurPosition);
}

void Curseur::draw(const glimac::TrackballCamera& cam) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	cubeCurseur.draw(cam);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//// Bind
	//GLCall(glBindVertexArray(m_vao));
	//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib));
	//cubeCurseur.m_shader.bind();

	//// Update model mat uniform
	//glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	//m_shader.setUniformMat4f("uViewProj", projMat * cam.getViewMatrix());


	//// Draw call
	//glDrawElementsInstanced(GL_TRIANGLES, std::size(cubeData::indices), GL_UNSIGNED_SHORT, 0, positionCubesExistants.size());
}

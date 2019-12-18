#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "app.h"
#include "CubesExistants.h"
#include "TrackballCamera.hpp"
#include "Curseur.h"


int main(int argc, char* argv[]) {
	App app;
	//activation de la transparence
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// couleur de la fenêtre
	glClearColor(197.0 / 255, 217.0 / 255, 222.0 / 255, 1);

	/* Création de la matrice MV  */
	glm::mat4 globalMVMatrix;

	//creation de la camera trackballCamera
	glimac::TrackballCamera camera;

	//camera parameter
	float zoom = 1.0f;
	float speed = 1.0f;

	// création des cubes
	const int nbCubesLigne = 10;
	const int nbCubesMonde = nbCubesLigne * nbCubesLigne * nbCubesLigne;

	CubesExistants cubesExistants;

	// sol état initial du monde 3 couches de blocs de même couleur
	for (int x = -(nbCubesLigne / 2); x < nbCubesLigne / 2; x++) {
		for (int y = -(3 / 2); y < 3 / 2; y++) {
			for (int z = -(nbCubesLigne / 2); z < nbCubesLigne / 2; z++) {
				cubesExistants.creerUnCube(glm::vec3(x, y, z),glm::vec4( 1.f, 0.f, 0.f, 0.1f));
			}
		}
	}

	//creation du curseur
	Curseur curseur;
	
	//application loop
	while (app.isRunning()) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				app.exit();
				break;

				/* Touche clavier */
			case SDL_KEYDOWN:

				if (e.key.keysym.sym == SDLK_z
					|| e.key.keysym.sym == SDLK_UP) {
					std::cout << "Z or UP pressed" << std::endl;
					camera.moveFront(zoom);
				}
				else if (e.key.keysym.sym == SDLK_s
					|| e.key.keysym.sym == SDLK_DOWN) {
					std::cout << "S or DOWN pressed" << std::endl;
					camera.moveFront(-zoom);
				}
				break;


			case SDL_MOUSEMOTION:

				//std::cout << "Mouse move: ";
				//std::cout << e.motion.xrel << " | " << e.motion.yrel << std::endl;
				if (e.motion.xrel != 0) {
					camera.rotateRight(float(e.motion.xrel) * speed);
				}
				if (e.motion.yrel != 0) {
					camera.rotateLeft(float(e.motion.yrel) * speed);
				}

				break;
			default:
				break;
			}
		}

		// rendering code 

		/* Calcul de la camera */
		globalMVMatrix = camera.getViewMatrix();

		app.beginFrame();

		curseur.cubeCurseur.draw(camera);
		cubesExistants.draw(camera);

		app.endFrame();
	}

	return 0;
}
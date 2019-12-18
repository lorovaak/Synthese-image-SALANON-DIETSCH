#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "app.h"
#include "cube.h"
#include "TrackballCamera.hpp"


int main(int argc, char *argv[]) {
    App app;
	//activation de la transparence
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// couleur de la fen�tre
    glClearColor(197.0/255, 217.0/255, 222.0/255, 1);

	/* Cr�ation de la matrice MV  */
	glm::mat4 globalMVMatrix;

	//creation de la camera trackballCamera
	glimac::TrackballCamera camera;

	//camera parameter
	float zoom = 1.0f;
	float speed = 1.0f;

	// cr�ation des cubes
	const int nbCubesLigne = 10;
	const int nbCubesMonde = nbCubesLigne* nbCubesLigne* nbCubesLigne;
	std::vector<Cube> cubesMonde(nbCubesMonde);

	int indice = 0;
	for (int x = -(nbCubesLigne / 2); x < nbCubesLigne / 2; x++) {
		for (int y = -(nbCubesLigne / 2); y < nbCubesLigne / 2; y++) {
			for (int z = -(nbCubesLigne / 2); z < nbCubesLigne / 2; z++) {
				cubesMonde[indice].position.x = x;
				cubesMonde[indice].position.y = y;
				cubesMonde[indice].position.z = z;
				indice += 1;
			}
		}
	}
	

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

		for (int i = 0; i < nbCubesMonde; i++) {
			//cubesMonde[i].draw(1,camera);
			cubesMonde[i].draw(camera);
		}
			   
        app.endFrame();
    }
    
    return 0;
}

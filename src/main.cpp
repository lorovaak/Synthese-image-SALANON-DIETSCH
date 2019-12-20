#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

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
	const int nbCubesLigne = 50;
	const int nbCubesMonde = nbCubesLigne * nbCubesLigne * nbCubesLigne;

	CubesExistants cubesExistants;

	// sol état initial du monde 3 couches de blocs de même couleur
	for (int x = -(nbCubesLigne / 2); x < nbCubesLigne / 2; x++) {
		for (int y = -(3.0 / 2); y < 3.0 / 2 - 1; y++) {
			for (int z = -(nbCubesLigne / 2); z < nbCubesLigne / 2; z++) {
				cubesExistants.creerUnCube(glm::vec3(x, y, z),glm::vec4(76.f/255, 9.f/255, 9.f/255, 1.f));
			}
		}
	}

	for (int x = -(nbCubesLigne / 2); x < nbCubesLigne / 2; x++) {
		for (int y = 3.0 / 2 - 1; y < 3.0 / 2; y++) {
			for (int z = -(nbCubesLigne / 2); z < nbCubesLigne / 2; z++) {
				cubesExistants.creerUnCube(glm::vec3(x, y, z), glm::vec4(125.f/255, 188.f/255, 123.f/255, 1.f));
			}
		}
	}

	cubesExistants.creerUnCube(glm::vec3(1, 1, 1), glm::vec4(1.f, 0.f, 0.f, 1.f));

	//creation du curseur
	Curseur curseur;

	
	//initialisation de imgui
	const char* glslVersion = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(app.m_window, app.m_glContext);
	ImGui_ImplOpenGL3_Init(glslVersion);
	ImGui::StyleColorsClassic();

	
	//application loop
	while (app.isRunning()) {


		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ImGui_ImplSDL2_ProcessEvent(&e);

			switch (e.type) {
			case SDL_QUIT:
			app.exit();
			break;

			// Touche clavier 
			case SDL_MOUSEWHEEL:

			if (e.wheel.y > 0) {
				std::cout << "mouse wheel" << std::endl;
				camera.moveFront(zoom);
			}
			else if (e.wheel.y < 0) {
				std::cout << "mouse wheel" << std::endl;
				camera.moveFront(-zoom);
			}
			break;

			
			case SDL_MOUSEMOTION:
				if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_RIGHT)) {
					if (e.motion.xrel != 0) {
						camera.rotateRight(float(e.motion.xrel) * speed);
					}
					if (e.motion.yrel != 0) {
						camera.rotateLeft(float(e.motion.yrel) * speed);
					}
				}
			break;


			

			case SDL_KEYDOWN:

				if (e.key.keysym.sym == SDLK_z) {
					std::cout << "Z pressed" << std::endl;
					curseur.move_y(1);
				}
				else if (e.key.keysym.sym == SDLK_s) {
					std::cout << "S pressed" << std::endl;
					curseur.move_y(-1);
				}
				else if (e.key.keysym.sym == SDLK_q) {
					std::cout << "Q pressed" << std::endl;
					curseur.move_x(-1);
				}
				else if (e.key.keysym.sym == SDLK_d) {
					std::cout << "D pressed" << std::endl;
					curseur.move_x(1);
				}
				else if (e.key.keysym.sym == SDLK_a) {
					std::cout << "U pressed" << std::endl;
					curseur.move_z(-1);
				}
				else if (e.key.keysym.sym == SDLK_e) {
					std::cout << "J pressed" << std::endl;
					curseur.move_z(1);
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

		app.onLoopIteration(cubesExistants, curseur);
		curseur.draw(camera);
		cubesExistants.draw(camera);

		app.endFrame();


	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyWindow(app.m_window);
	SDL_Quit();

	return 0;
}
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

//////////
// MAIN //
//////////

int main(int argc, char* argv[]) {
	App app;

	//activation de la transparence
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// couleur de la fen�tre
	glClearColor(197.0 / 255, 217.0 / 255, 222.0 / 255, 1);

	/* Cr�ation de la matrice MV  */
	glm::mat4 globalMVMatrix; // pour la camera 

	//creation de la camera trackballCamera
	glimac::TrackballCamera camera;

	//camera parameters
	float zoom = 1.0f;
	float speed = 1.0f;

	// cr�ation des cubes
	const int nbCubesLigne = 50;  // nombres de cubes par arretes 
	const int nbCubesMonde = nbCubesLigne * nbCubesLigne * nbCubesLigne; // nombre de cubes du monde
	CubesExistants cubesExistants; // liste des cubes existants dans le monde

	// creation du sol ; �tat initial du monde 3 couches de blocs de m�me couleur
		// les cubes du fond sont bruns 
		for (int x = -(nbCubesLigne / 2); x < nbCubesLigne / 2; x++) {
			for (int y = -(3.0 / 2); y < 3.0 / 2 - 1; y++) {
				for (int z = -(nbCubesLigne / 2); z < nbCubesLigne / 2; z++) {
					cubesExistants.creerUnCube(glm::vec3(x, y, z),glm::vec4(76.f/255, 9.f/255, 9.f/255, 1.f));
				}
			}
		}
		// les cubes de la couche superieure sont verts 
		for (int x = -(nbCubesLigne / 2); x < nbCubesLigne / 2; x++) {
			for (int y = 3.0 / 2 - 1; y < 3.0 / 2; y++) {
				for (int z = -(nbCubesLigne / 2); z < nbCubesLigne / 2; z++) {
					cubesExistants.creerUnCube(glm::vec3(x, y, z), glm::vec4(125.f/255, 188.f/255, 123.f/255, 1.f));
				}
			}
		}

	//creation du curseur
	Curseur curseur;

	// initialisation de imgui

	const char* glslVersion = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(app.m_window, app.m_glContext);
	ImGui_ImplOpenGL3_Init(glslVersion);
	ImGui::StyleColorsClassic();

	//////////////////////
	// application loop //
	//////////////////////

	while (app.isRunning()) 
	{
		// gestion des evenements 

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ImGui_ImplSDL2_ProcessEvent(&e); // gestion des evenements par imgui

			switch (e.type) {
			case SDL_QUIT:
			app.exit();
			break;

			// gestion de la souris 

			case SDL_MOUSEWHEEL:

				// zoom et dezoom avec la molette 

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

				// deplacer la trackball avec le curseur 

				if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_RIGHT)) {
					if (e.motion.xrel != 0) {
						camera.rotateRight(float(e.motion.xrel) * speed);
					}
					if (e.motion.yrel != 0) {
						camera.rotateLeft(float(e.motion.yrel) * speed);
					}
				}
			break;

			// gestion des touches clavier
			
			case SDL_KEYDOWN:

				// deplacement du curseur 

				if (e.key.keysym.sym == SDLK_UP) {
					std::cout << "UP pressed" << std::endl;
					curseur.move_y(1);
				}
				else if (e.key.keysym.sym == SDLK_DOWN) {
					std::cout << "DOWN pressed" << std::endl;
					curseur.move_y(-1);
				}
				else if (e.key.keysym.sym == SDLK_LEFT) {
					std::cout << "LEFT pressed" << std::endl;
					curseur.move_x(-1);
				}
				else if (e.key.keysym.sym == SDLK_RIGHT) {
					std::cout << "RIGHT pressed" << std::endl;
					curseur.move_x(1);
				}
				else if (e.key.keysym.sym == SDLK_a) {
					std::cout << "A pressed" << std::endl;
					curseur.move_z(-1);
				}
				else if (e.key.keysym.sym == SDLK_e) {
					std::cout << "E pressed" << std::endl;
					curseur.move_z(1);
				}

				break;

			default:
				break;
			}
		}

		// Rendering code 

			// Calcul de la camera 

			globalMVMatrix = camera.getViewMatrix();

			// Begin frame 

			app.beginFrame();

			// Iteration loop

			app.onLoopIteration(cubesExistants, curseur);

			// Draw a chaque iteration du curseur et des cubes

			curseur.draw(camera); // draw le curseur 
			cubesExistants.draw(camera); // draw tous les cubes existants en une seule fois

			// End frame

			app.endFrame();


	} // sortie de while running 

	// Liberation des ressources Imgui 

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// Liberation des ressources SDL

	SDL_DestroyWindow(app.m_window);
	SDL_Quit();

	return 0;

} // fin du main
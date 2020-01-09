#include "app.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <debug_break/debug_break.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>

bool App::m_instanciated = false;

App::App() 
	:couleurDefaut(253.f/255, 187.f/255, 209.f/255, 1)
{
    assert(!m_instanciated && "App already created !");
	m_instanciated = true;
	m_bShowImGUIDemoWindow = false;

    spdlog::set_pattern("[%l] %^ %v %$");

	initSDL();

	glEnable(GL_DEPTH_TEST);
}

App::~App() {
	SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void App::beginFrame() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
}

void App::endFrame() const {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(m_window);
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GETTERS & SETTERS //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool App::isRunning() const { return m_running; }
void App::exit() { m_running = false; }

/////////////////////////////////////////////////////////////////////////////
///////////////////////////// PRIVATE METHODS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void App::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		spdlog::critical("[SDL2] Unable to initialize SDL: {}", SDL_GetError());
		debug_break();
	}
	
    // Use OpenGL 3.3
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_LoadLibrary(NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Various attributes
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	
	
	m_window = SDL_CreateWindow(
		"Toto's cubic world",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		650, 650,
		SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
	if (m_window == nullptr) {
        spdlog::critical("[SDL2] Window is null: {}", SDL_GetError());
        debug_break();
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if (m_glContext == nullptr) {
        spdlog::critical("[SDL2] OpenGL context is null: {}",  SDL_GetError());
        debug_break();
    }

	SDL_GL_MakeCurrent(m_window, m_glContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

	if (!gladLoadGL()) {
		spdlog::critical("[Glad] Glad not init");
		debug_break();
	}
}

void App::onLoopIteration(CubesExistants& cubesExistants, Curseur& curseur) {
	// C'est la qu'on met tout le code qui se repete a chaque frame

	// ImGui windows
	ImGui::Begin("Menu");

	if (ImGui::Button("Creer cube")) 
	{
		std::cout << curseur.curseurPosition.x << " " << curseur.curseurPosition.y << " " << curseur.curseurPosition.z << std::endl;
		cubesExistants.creerUnCube(curseur.curseurPosition, couleurDefaut);
	}
	ImGui::SameLine();

	if (ImGui::Button("Supprimer cube"))
	{
		cubesExistants.supprimerCube(curseur.curseurPosition);
	}
	

	if (ImGui::Button("Extruder")) {
		glm::vec4 couleurExtrusion = couleurDefaut;
		if (cubesExistants.indiceCube(curseur.curseurPosition) != -1) {
			couleurExtrusion = cubesExistants.couleursCubesExistants[cubesExistants.indiceCube(curseur.curseurPosition)];
		}
		cubesExistants.extrusion(curseur.curseurPosition, couleurExtrusion);
	}
	ImGui::SameLine();


	if (ImGui::Button("Creuser")) {
		// couleurExtrsuion = couleur du cube à la position de mon curseur
		if (cubesExistants.indiceCube(curseur.curseurPosition) != -1) {
			glm::vec4 couleurExtrusion2 = cubesExistants.couleursCubesExistants[cubesExistants.indiceCube(curseur.curseurPosition)];
			cubesExistants.creuser(curseur.curseurPosition, couleurExtrusion2);
		}

		//std::cout << curseur.curseurPosition.y << std::endl;
	}

	ImGui::ColorEdit4("Couleur", (float*)&couleurDefaut);
	if (ImGui::Button("Modifier la couleur")) {
		cubesExistants.changeCouleur(curseur.curseurPosition, couleurDefaut);
	}
	ImGui::SameLine();


	if (ImGui::Button("Mode nuit"))
	{
		cubesExistants.lightEffect = glm::vec4 (0.2f, 0.2f, 0.2f, 1.0f);
	}

	if (ImGui::Button("Mode jour"))
	{
		cubesExistants.lightEffect = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	if (ImGui::Button("Save"))
	{
		save(cubesExistants, "./save/", "sauvegarde 1");
	}

	if (ImGui::Button("Load"))
	{
		load(cubesExistants, "./save/", "sauvegarde 1");
	}

	ImGui::End();
	

	if (m_bShowImGUIDemoWindow) // Show the big demo window 
		ImGui::ShowDemoWindow(&m_bShowImGUIDemoWindow);

}



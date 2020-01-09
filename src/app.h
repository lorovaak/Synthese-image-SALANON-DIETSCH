#pragma once

#include <SDL2/SDL.h>
#include <Curseur.h>
#include <save.h>

/**
 * @brief Base root of the app
 */
class App {
public:
    App();
    ~App();

    /**
     * @brief Prepare for a new frame
     * @note Must be called after handling SDL events
     */
    void beginFrame() const;

    /**
     * @brief Render the preparred frame
     */
    void endFrame() const;

    bool isRunning() const;
    void exit();
	void onLoopIteration(CubesExistants& cubesExistants, Curseur& curseur);



private:
    void initSDL();

public :
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_bShowImGUIDemoWindow;
	glm::vec4 couleurDefaut;

private:
    static bool m_instanciated;
    bool m_running;

};

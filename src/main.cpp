#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "app.h"
#include "cube.h"

int main(int argc, char *argv[]) {
    App app;
    Cube myCube;
    Cube myCube2;

    glClearColor(1, 0, 1, 1);

    while (app.isRunning()) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT: app.exit();

            case SDL_KEYDOWN:
                if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    myCube.position.x--;
                } else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    myCube.position.x++;
                } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                    myCube.position.y++;
                } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    myCube.position.y--;
                } else if (e.key.keysym.scancode == SDL_SCANCODE_PAGEUP) {
                    myCube.position.z++;
                } else if (e.key.keysym.scancode == SDL_SCANCODE_PAGEDOWN) {
                    myCube.position.z--;
                }

            default: break;
            };
        }

        app.beginFrame();

        myCube.draw();
        myCube2.draw();

        app.endFrame();
    }
    
    return 0;
}

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "CubesExistants.h"

using namespace std;

int save(CubesExistants &cubesExistants, string filepath, string filename);
void load(CubesExistants &cubesExistants, string filepath, string filename);
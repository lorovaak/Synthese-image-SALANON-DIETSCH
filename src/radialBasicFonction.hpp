#pragma once

#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "CubesExistants.h"

using namespace Eigen;

const double phi(const double &d);
const double norm(const glm::vec3 vec1);
const VectorXd find_omega(unsigned int nbPointsControle, std::vector<glm::vec3> PositionCubesControle, glm::vec4 Poids);
void gener_terrain(CubesExistants &cubesExistants, const glm::vec3 PositionCubeActuel, unsigned int nbPointsControle, std::vector<glm::vec3> PositionCubesControle, const glm::vec4 Poids, const int nbCubesLignes);
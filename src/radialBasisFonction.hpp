#pragma once

#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "CubesExistants.h"

using namespace Eigen;

const double phi(const double &d);
const double norm(const glm::vec3 vec1);
const VectorXd find_omega(const unsigned int& nbPointsControle, const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids);
void gener_terrain(CubesExistants& cubesExistants, const glm::vec3 PositionCubeActuel, const unsigned int& nbPointsControle, const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids, const int& nbCubesLignes);

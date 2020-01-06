#pragma once

#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "CubesExistants.h"

using namespace Eigen;

namespace RBF
{
	template <typename T>
	const T phi(const T& d) {
		return exp(-15 * d * d);
		// return sqrt(1 + 0.2*10E-10 * d*d); // multiquadratic
		// return 1.0f / (1 + 0.2 * 10E10 * d * d);
	}

	const double norm(const glm::vec3 vec1);
	const VectorXd find_omega(const unsigned int& nbPointsControle, const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids);
	void gener_terrain(CubesExistants& cubesExistants, const glm::vec3 PositionCubeActuel, const unsigned int& nbPointsControle, const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids, const int& nbCubesLignes);

}


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
		 return  exp(-0.02 * d * d); // gaussian
		// return  -0.01 * d * d;
		// return exp(-T(0.4) * d * d);
		// return sqrt(1 + 0.2*0.2 * d*d); // multiquadratic
		// return 1.0f / (1 + 0.02 * 0.02 * d * d); // inverse quadratic
	}

	const double norm(const glm::vec3& vec1);
	const VectorXd find_omega(const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids);
	void gener_terrain(CubesExistants& cubesExistants, const std::vector<glm::vec3>& evaluationPts, const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids);

}


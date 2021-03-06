#include <iostream>
#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp >

#include "radialBasisFonction.hpp"
#include "CubesExistants.h"

using namespace Eigen;

// Calcul norme
const double RBF::norm(const glm::vec3& vec1) {
    return glm::length2(vec1);
}


// Calcul des omega_i

const VectorXd RBF::find_omega(const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids) // vecteur Eigen pour utiliser LU (ne fonctionne qu'avec des vect de Eigen)
{
    assert(PositionCubesControle.size() == Poids.size() && "Need the same number of elements in PositionCubesControle and in Poids");

    MatrixXd M_contrainte = MatrixXd::Zero(PositionCubesControle.size(), PositionCubesControle.size());

    // Remplissage de M_contrainte

    for (int i = 0; i < PositionCubesControle.size(); i++) {
        for (int j = 0; j < PositionCubesControle.size(); j++) {
            M_contrainte(i, j) = phi(glm::distance2(PositionCubesControle[i], PositionCubesControle[j]));
        }
    }

    //méthode de résolution de M_contrainte*omega = poids
    // Par méthode LU car plus rapide

    PartialPivLU<MatrixXd> lu(M_contrainte);
    VectorXd omega = lu.solve(Poids);

    return omega;
}

// Fonction pour générer le terrain

void RBF::gener_terrain(CubesExistants& cubesExistants, const std::vector<glm::vec3>& evaluationPts, const std::vector<glm::vec3>& PositionCubesControle, const Eigen::VectorXd& Poids) {

    VectorXd omega = find_omega(PositionCubesControle, Poids);

    VectorXd evaluatedPts = VectorXd::Zero(evaluationPts.size());

    for (int i = 0; i < evaluationPts.size(); i++) {

        for (int j = 0; j < PositionCubesControle.size(); j++) {
            evaluatedPts[i] += omega[j] * phi(glm::distance2(evaluationPts[i], PositionCubesControle[j]));
        }
    }

    for (int i = 0; i < evaluationPts.size(); i++) {
        if (evaluatedPts[i] > 0) {
            cubesExistants.creerUnCube(evaluationPts[i], glm::vec4(117.f / 255, 5.f / 255, 31.f / 255, 1.0f));
        }
    }


}

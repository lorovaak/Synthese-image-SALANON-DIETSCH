#include <iostream>
#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>


#include "radialBasisFonction.hpp"
#include "CubesExistants.h"

using namespace Eigen;

// Calcul norme
const double RBF::norm(const glm::vec3 vec1){
    return( (double)sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z ));
}


// Calcul des omega_i

const VectorXd RBF::find_omega(const unsigned int &nbPointsControle, const std::vector<glm::vec3> &PositionCubesControle, const Eigen::VectorXd &Poids) // vecteur Eigen pour utiliser LU (ne fonctionne qu'avec des vect de Eigen)
{ 
    assert(PositionCubesControle.size() == Poids.size() && "Need the same number of elements in PositionCubesControle and in Poids");
    
    MatrixXd M_contrainte = MatrixXd::Zero(nbPointsControle, nbPointsControle);
    
    // Remplissage de M_contrainte

    for(int i=0; i<nbPointsControle; i++){
        for(int j=0; j<nbPointsControle; j++){
            M_contrainte(i,j) = phi(norm(PositionCubesControle[i] - PositionCubesControle[j]));
           // std::cout << M_contrainte(i, j) << std::endl;
        }
    }

    //méthode de résolution de M_contrainte*omega = poids
    // Par méthode LU car plus rapide

    PartialPivLU<MatrixXd> lu(M_contrainte);
    VectorXd omega = lu.solve(Poids);

    //for (int i = 0; i < omega.size(); i++)
    //{
    //    std::cout << omega[i] << std::endl;
    //}

    return omega;
}

// Fonction pour générer le terrain

void RBF::gener_terrain(CubesExistants &cubesExistants, const glm::vec3 PositionCubeActuel, const unsigned int &nbPointsControle, const std::vector<glm::vec3> &PositionCubesControle, const Eigen::VectorXd &Poids, const int &nbCubesLignes) {

    VectorXd omega = find_omega(nbPointsControle, PositionCubesControle, Poids);

 /*   for (int i = 0; i < omega.size(); i++)
    {
        std::cout << omega[i] << std::endl;

    }*/
        double poidsCubeActuel = 0.0;
    

    for (int i = 0; i < nbPointsControle; i++)
    {
        poidsCubeActuel += omega[i] * phi(norm((PositionCubeActuel - PositionCubesControle[i])));
    }

    if (poidsCubeActuel > 0.0 )
    {
        cubesExistants.creerUnCube(PositionCubeActuel, glm::vec4(2.f / 255, 42.f / 255, 120.f / 255, 1.f));
    }


}

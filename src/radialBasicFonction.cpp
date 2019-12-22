//#include <iostream>
//#include <Eigen/Dense>
//#include <SDL2/SDL.h>
//#include <glad/glad.h>
//#include <spdlog/spdlog.h>
//#include <glm/glm.hpp>
//
//
//#include "radialBasicFonction.hpp"
//#include "cube.h"
//
//using namespace Eigen;
//
//// Fonction Phi
//const double phi(const double &d){
//    return exp(-0.2*d*d);
//}
//
//// Calcul norne
//const double norm(const glm::vec3 vec1){
//    return( (double)sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z ));
//} 
//
//// Calcul des omega_i
//
//const VectorXd find_omega(unsigned int nbPointsControle, std::vector<Cube*> v_pointsControle){
//    
//    MatrixXd M_contrainte = MatrixXd::Zero(nbPointsControle, nbPointsControle);
//    
//    VectorXd poids = VectorXd::Ones(nbPointsControle);
//
//    //Remplissage du vecteur de poids des points de controles
//
//    for(int h=0; h<nbPointsControle; h++){
//        poids[h] = v_pointsControle[h]->poids;
//    }
//
//    // Remplissage de M_contrainte
//    for(int i=0; i<nbPointsControle; i++){
//        for(int j=0; j<nbPointsControle; j++){
//            M_contrainte(i,j) = phi(norm(v_pointsControle[i]->position-v_pointsControle[j]->position));
//        }
//    }
//    
//    //méthode de résolution de M_contrainte*omega=poids
//    //On choisit la méthode LU car elle est plus rapide
//    PartialPivLU<MatrixXd> lu(M_contrainte);
//    VectorXd omega = lu.solve(poids);
//
//    return omega;
//}
//
////création de notre fonction pour générer le terrain
//void gener_terrain(unsigned int nbPointsControle, Cube* actualCube, const std::vector<Cube*> v_pointsControle){
//    VectorXd omega = find_omega(nbPointsControle, v_pointsControle);
//    for(int i=0; i<nbPointsControle; i++){
//
//        if (actualCube->poids == 0) actualCube->poids += omega[i]*phi(norm((actualCube->position-v_pointsControle[i]->position)));
//    }
//}

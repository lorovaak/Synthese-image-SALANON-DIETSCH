Synthese-image-SALANON-DIETSCH

// GENERATION FENETRE
La couleur de la fenêtre peut être modifiée dans app.cpp

// GENERATION DU MONDE
Le paramètre nbCubesLignes dans le main permet de définir la longueur du pavé initial dans le monde (de taille nbCubesLignes x nbCubesLignes x 3).
Les couleurs des cubes du monde intial sont à définir dans le main.

//CAMERA
La caméra se déplace à la sourie en maintenant le clic gauche ou le clic droit enfoncé.
La vitesse (speed) et le zoom de la caméra peuvent être modifiés dans le main.

// CURSEUR 
Le curseur se déplace avec les flèches du clavier pour aller de droite à gauche et de haut en bas et avec les lettres A et E pour aller d'avant en arrière.
San couleur peut être modifiée dans le main lors de l'appel de curseur.draw

// LUMIERES
La couleur de la lumière peut être modifiée dans app.cpp
La position de la lumière peut être modifiée dans CubesExistants.cpp au moment de la déclaration de la variable uniform uLightPos.

// RBF
Les points de contrôle pour les RBF sont à définir directement dans le main (leur position et leur poid).
Il faut changer le paramètre nbPointControle en fonction du nombre de points de contrôle.
Pour changer la fonction Phi utilisée pour les RBF, il faut l'écrire dans RadialBasisFunction.hpp
La couleur des cubes générés se modifie dans RadialBasisFunction.cpp dans la fonction gener_terrain


#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "CubesExistants.h"
#include "save.h"

using namespace std;

int save(CubesExistants &cubesExistants, string filepath, string filename){
    ofstream file;
    file.open(filepath + filename);
    if(file.bad()) return 1;
    file.seekp(0,ios::end);
    for(int i=0; i<cubesExistants.positionCubesExistants.size(); i++)
    {
        file << i << " " << cubesExistants.positionCubesExistants[i].x << " " << cubesExistants.positionCubesExistants[i].y << " " << cubesExistants.positionCubesExistants[i].z << " " << cubesExistants.couleursCubesExistants[i].x << " " << cubesExistants.couleursCubesExistants[i].y << " " << cubesExistants.couleursCubesExistants[i].z << " " << cubesExistants.couleursCubesExistants[i].w << endl;
    }
    file.close();
    cout<< "Saved success" << endl;
    return 0;
}

void load(CubesExistants &cubesExistants, string filepath, string filename){
    ifstream file(filepath + filename, ios::in | ios::binary);
    string ligne;
    vector<string> texte;

    if(file.is_open()){
        cout<<"fichier ouvert"<<endl;
        while(getline(file, ligne)){
            texte.push_back(move(ligne));
        }

 
        for (int i=0; i<texte.size(); i++)
        {
            sscanf(texte[i].c_str(), "%d %f %f %f %f %f %f %f", & i, &cubesExistants.positionCubesExistants[i].x, &cubesExistants.positionCubesExistants[i].y, &cubesExistants.positionCubesExistants[i].z, &cubesExistants.couleursCubesExistants[i].x, &cubesExistants.couleursCubesExistants[i].y, &cubesExistants.couleursCubesExistants[i].z, &cubesExistants.couleursCubesExistants[i].w);
        }
    }
    else cout << "This file doesn't exist" << endl;
}
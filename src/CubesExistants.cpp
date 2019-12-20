#include "CubesExistants.h"

#include <glm/gtc/matrix_transform.hpp>
#include "gl-exception.h"

namespace cubeData {
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3
    const glm::vec3 positions[] = {
        // Front v0,v1,v2,v3
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, 0.5),
        // Right v0,v3,v4,v5
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, -0.5),
        // Top v0,v5,v6,v0.5	
        glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-0.5, 0.5, 0.5),
        // Left v0.5,v6,v7,v2	
        glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, -0.5, 0.5),  
        // Bottom v7,v4,v3,v2
        glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5), 
        // Back v4,v7,v6,v5	
        glm::vec3(0.5, -0.5, -0.5), glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5, 0.5, -0.5)
    };

    const glm::vec3 normals[] = {
        glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),
        glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0),
        glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0),
        glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1)
    };

    const unsigned short indices[] = {
        0, 1, 2,   2, 3, 0,       // front
        4, 5, 6,   6, 7, 4,       // right
        8, 9, 10,  10,11,8,       // top
        12,13,14,  14,15,12,      // left
        16,17,18,  18,19,16,      // bottom
        20,21,22,  22,23,20		  // back
    };
}

CubesExistants::CubesExistants()
    : m_vao(0), m_ib(0), m_shader("res/shaders/basic.vert", "res/shaders/basic.frag")
{
    // ------------------ Vertex Buffer
    unsigned int posVB;
    {
        GLCall(glGenBuffers(1, &posVB));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVB));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::positions), cubeData::positions, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }


	// on crée le buffer
	glGenBuffers(1, &vbPositionsCubesID);
	glGenBuffers(1, &vbCouleursCubesID);
	
    
    // ------------------ Vertex Array
    {
        GLCall(glGenVertexArrays(1, &m_vao));
        GLCall(glBindVertexArray(m_vao));

        // Vertex input description
        {
            GLCall(glEnableVertexAttribArray(0));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVB));
            GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL));
        }

		glBindBuffer(GL_ARRAY_BUFFER, vbPositionsCubesID);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glVertexAttribDivisor(1, 1);

		glBindBuffer(GL_ARRAY_BUFFER, vbCouleursCubesID);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glVertexAttribDivisor(2, 1);
        
        GLCall(glBindVertexArray(0));
    }

    // ------------------ Index buffer
    {
        GLCall(glGenBuffers(1, &m_ib));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeData::indices), cubeData::indices, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    // ------------------ Default values for uniforms
    m_shader.bind();
    {
        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 viewProjMat = projMat * viewMat;
        m_shader.setUniformMat4f("uViewProj", viewProjMat);
    }
    m_shader.unbind();
}

CubesExistants::~CubesExistants()
{
}

//void CubesExistants::draw(int i,const glimac::TrackballCamera &cam) {
void CubesExistants::draw(const glimac::TrackballCamera & cam) {
	// Bind
	GLCall(glBindVertexArray(m_vao));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib));
	m_shader.bind();

	// Update model mat uniform
	glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	m_shader.setUniformMat4f("uViewProj", projMat *cam.getViewMatrix());


	// Draw call
	glDrawElementsInstanced(GL_TRIANGLES, std::size(cubeData::indices), GL_UNSIGNED_SHORT, 0, positionCubesExistants.size());
}

void CubesExistants::updateGPU() {
	
	// on le bind pour que la ligne suivante s'applique bien à ce buffer ci
	glBindBuffer(GL_ARRAY_BUFFER, vbPositionsCubesID);
	// on envoie toutes nos données au GPU
	glBufferData(GL_ARRAY_BUFFER, positionCubesExistants.size() * sizeof(glm::vec3), &positionCubesExistants[0], GL_STATIC_DRAW);
	// on unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// on le bind pour que la ligne suivante s'applique bien à ce buffer ci
	glBindBuffer(GL_ARRAY_BUFFER, vbCouleursCubesID);
	// on envoie toutes nos données au GPU
	glBufferData(GL_ARRAY_BUFFER, couleursCubesExistants.size() * sizeof(glm::vec4), &couleursCubesExistants[0], GL_STATIC_DRAW);
	// on unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubesExistants::creerUnCube(glm::vec3 coordonees, glm::vec4 couleurs) {
	// On gere la position du cube créé
	positionCubesExistants.push_back(coordonees);

	// On gère la couleur du cube créé 
	couleursCubesExistants.push_back(couleurs);

	// mise à jour du GPU
	updateGPU();
}

void CubesExistants::déplacerCube(glm::vec3 positionActuelle, glm::vec3 nouvellePosition) {
	int indice = indiceCube(positionActuelle);
	positionCubesExistants[indice]=nouvellePosition;
	updateGPU();
}

void CubesExistants::supprimerCube(const glm::vec3 position) {
	int indiceCubeSupp = indiceCube(position);
	int indiceDernier = positionCubesExistants.size()-1;
	std::swap(indiceCubeSupp, indiceDernier);
	updateGPU();
}

int CubesExistants::indiceCube(const glm::vec3 position) {
	for (int i = 0; i < positionCubesExistants.size(); ++i) {
		if(glm::length(position-positionCubesExistants[i]) < 0.1f){
			return i;
		}
	}
	return -1;
}

void CubesExistants::changeCouleur(glm::vec3 cubePosition, glm::vec4 nouvelleCouleur) {
	if (indiceCube(cubePosition)!=-1) {
		int indice = indiceCube(cubePosition);
		couleursCubesExistants[indice] = nouvelleCouleur;
		updateGPU();
	}
}

void CubesExistants::cubeExiste(glm::vec3 position) {
	
}

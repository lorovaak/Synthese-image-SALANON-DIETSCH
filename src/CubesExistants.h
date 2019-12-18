#pragma once

#include <glm/glm.hpp>
#include "TrackballCamera.hpp"
#include "shader.h"
#include <vector>
#include <glad/glad.h>

class CubesExistants {
public:
    CubesExistants();
    ~CubesExistants();
	void draw(const glimac::TrackballCamera& cam);
    void draw();
	void creerUnCube(glm::vec3 coordonees);

public:
	std::vector<glm::vec3> positionCubesExistants;

private:
    unsigned int m_vao;
    unsigned int m_ib;
    Shader m_shader;
	GLuint vbPositionsCubesID;
};

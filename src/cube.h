#pragma once

#include <glm/glm.hpp>
#include "TrackballCamera.hpp"
#include "shader.h"

class Cube {
public:
    Cube();
    ~Cube();
	void draw(const glimac::TrackballCamera& cam);
    void draw();
    
public:
    glm::vec3 position;

private:
    unsigned int m_vao;
    unsigned int m_ib;
    Shader m_shader;
};

#include <glm/glm.hpp>
#include "TrackballCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>


namespace glimac {

  TrackballCamera::TrackballCamera()
    : _fDistance(-75.0f), _fAngleX(25.0f), _fAngleY(0.0f)
  {
  }
  void TrackballCamera::moveFront(const float &delta) 
  {
    if ( delta > 0 && _fDistance >= -1.0f ) return;
    _fDistance += delta;
  }
  void TrackballCamera::rotateLeft(const float &degrees) 
  {
    _fAngleX += degrees;
  }
  void TrackballCamera::rotateRight(const float &degrees) 
  {
    _fAngleY += degrees;
  }
  glm::mat4 TrackballCamera::getViewMatrix() const
  {
    glm::mat4 VM = glm::mat4(1.f);
    VM = glm::translate( VM, glm::vec3(0.0f, 0.0f, _fDistance));
    VM = glm::rotate( VM, glm::radians(_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    VM = glm::rotate( VM, glm::radians(_fAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    return VM;
  }
  
}
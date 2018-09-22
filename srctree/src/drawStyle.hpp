#pragma once 

#include "opengl.hpp"
#include "glm/glm.hpp"

#include "cgra/mesh.hpp"
#include "cgra/shader.hpp"

//each composite object returns an array of draw styles
// instead of each object overriding a draw function,
// the app implements a draw function that iterates
// over the object's array of draw styles. 

//each vao/mesh has a drawStyle

struct uniforms{
  std::map<String, int   *> uniforms1i;
  std::map<String, float *> uniforms1f;
};

struct drawStyle{
  //all ptrs can be null
  //this allows drawStyles with only uniform settings
  //to be included like optional lines
  cgra::Program * prog;
  cgra::Mesh * m_mesh;
  glm::mat4 * wmMat;
  uniforms * ufs;

};

#pragma once

#include "includes-l1.hpp"

//each composite object returns an array of draw styles
// instead of each object overriding a draw function,
// the app implements a draw function that iterates
// over the object's array of draw styles.

//each vao/mesh has a drawStyle

struct uniforms{
  std::map<std::string, int * > uniforms1i;
  std::map<std::string, float * > uniforms1f;
};

struct drawStyle{
  //all ptrs can be null
  //this allows drawStyles with only uniform settings
  //to be included like optional lines
  cgra::Program * prog;
  cgra::Mesh * m_mesh;
  glm::mat4 * wmMat;
  uniforms * unfms;

};

#pragma once

#include "includes-l1.hpp"
//each composite object returns an array of draw styles
// instead of each object overriding a draw function,
// the app implements a draw function that iterates
// over the object's array of draw styles.

//each vao/mesh has a drawStyle

struct drawStyle{
  cgra::Program prog;
  std::map<String, * float> uniforms1f;
  std::map<String, * int> uniforms1i;

  cgra::Mesh * m_mesh;
}

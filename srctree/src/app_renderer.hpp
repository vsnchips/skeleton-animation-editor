#pragma once

#include "includes-l1.hpp"
#include "drawStyle.hpp"
// app renderer

class app_renderer{

  public:

  cgra::Program * c_prog; //current program

  void execute(std::vector<drawStyle> & target);

  void passUniforms(cgra::Program * p, uniforms * unfms);


};

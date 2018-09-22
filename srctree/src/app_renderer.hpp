#pragma once

#include "includes-l1.hpp"
#include "drawStyle.hpp"
// app renderer

class app_renderer{

  public:
  
    app_renderer();

  cgra::Program * c_prog; //current program

  cgra::Program pickProg;

  //rendering options
  bool previewPick = false;

  void execute(std::vector<drawStyle> & target);

  void passUniforms(cgra::Program * p, uniforms * unfms);

  //dev
  void loadPickShader();

};

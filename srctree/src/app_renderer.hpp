#pragma once

#include "includes-l1.hpp"
#include "drawStyle.hpp"
// app renderer

class app_renderer{

  public:
  
    app_renderer();

  cgra::Program * c_prog; //current program

  cgra::Program pickProg;

  glm::mat4 projection;
  glm::mat4 view;

  // window stuff
  glm::vec2 m_viewportSize;

  //rendering options
  bool previewPick = false;

  void execute(std::vector<drawStyle> & target);

  void passUniforms(cgra::Program * p, uniforms * unfms);

  //dev
  void loadPickShader();

  void pickDraw(std::vector<drawStyle> & t);
  int pickTest( std::vector<drawStyle> target, glm::vec2 & m_mousePosition);






};

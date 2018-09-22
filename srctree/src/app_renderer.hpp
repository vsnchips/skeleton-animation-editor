#pragma once
#include "pattern.hpp"
// app renderer

class app_renderer{

  public:
  
  cgra::Program * c_prog; //current program
  
  void Render(std::vector<drawStyle> target);

  void setUniforms(cgra::Program p, uniforms & unfms);

  void setMats(glm::mat4 pv, glm::mat4 wm);
  
};

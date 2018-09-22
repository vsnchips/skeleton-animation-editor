#pragma once
#include "app_renderer.hpp"

void app_renderer::Render(std::vector<drawStyle> target){

  for (drawStyle d : target){
    d.prog.setModelMatrix(d.wmMat);
  }

  if (c_prog != d.prog){
    d.prog->use();
    setUniforms(d.prog,d.unfms);
  }
}


void app_renderer::setUniforms(cgra::Program * p, uniforms * unfms){
//ints
  for (auto const& p : unfms.uniforms1i){
      glUniform1i(glGetUniformLocation(c_prog->m_program,p.first),p.second);
  }
//floats
  for (auto const& p : unfms.uniforms1f){
      glUniform1f(glGetUniformLocation(c_prog->m_program,p.first),p.second);
  }
}

void app_renderer::setMats(glm::mat4 & pv, glm::mat4 & wm){
//ints
  if (!c_prog){
  printf("Renderer has no reference to the shader program to send the transform matrices to.\n")
  return;
  }
  else{
  c_prog.setModelMatrix(wm);
  c_prog.setViewMatrix(pv);
  }

}

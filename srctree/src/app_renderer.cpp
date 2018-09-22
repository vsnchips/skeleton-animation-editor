#pragma once
#include "app_renderer.hpp"

void app_renderer::passUniforms(cgra::Program * p, uniforms * unfms){
//ints
  for (auto const& v : unfms->i1){
          glUniform1i(glGetUniformLocation(c_prog->m_program,v.first.c_str()),v.second);
  }
//floats
  for (auto const& v : unfms->f1){
      glUniform1f(glGetUniformLocation(c_prog->m_program,v.first.c_str()),v.second);
  }
  //vec3s
  for (auto const& v : unfms->f3){
      glUniform3fv(glGetUniformLocation(c_prog->m_program,v.first.c_str()),1,&v.second[0]);
  }
  //mat4s
  for (auto const& v : unfms->m4){
      glUniformMatrix4fv(glGetUniformLocation(c_prog->m_program,v.first.c_str()),1, GL_FALSE,&v.second[0][0]);
  }
}


void app_renderer::execute(std::vector<drawStyle> & target){

   for (drawStyle d : target){
       if (d.prog){
     if (c_prog != d.prog){
       //d.prog->use();
       c_prog = d.prog;
       //d.prog->setViewMatrix(currentProjViewMat);
     }
   }

  passUniforms(d.prog,&d.unfms);

   if (d.m_mesh){
       d.m_mesh->draw();
   }
 }
}

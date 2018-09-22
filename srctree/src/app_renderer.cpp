#pragma once
#include "app_renderer.hpp"

app_renderer::app_renderer(){

  loadPickShader();

}

void app_renderer::loadPickShader(){
  pickProg = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        CGRA_SRCDIR "/res/shaders/pick.fs.glsl"
           );
}

void app_renderer::passUniforms(cgra::Program * p, uniforms * unfms){
  //ints
  for (auto const& v : unfms->i1){
    glUniform1i(glGetUniformLocation(p->m_program,v.first.c_str()),v.second);
  }
  //floats
  for (auto const& v : unfms->f1){
    glUniform1f(glGetUniformLocation(p->m_program,v.first.c_str()),v.second);
  }
  //vec3s
  for (auto const& v : unfms->f3){
    glUniform3fv(glGetUniformLocation(p->m_program,v.first.c_str()),1,&v.second[0]);
  }
  //mat4s
  for (auto const& v : unfms->m4){
    glUniformMatrix4fv(glGetUniformLocation(p->m_program,v.first.c_str()),1, GL_FALSE,&v.second[0][0]);
  }
}


void app_renderer::execute(std::vector<drawStyle> & target){

  // Pick Preview
  if (previewPick){
    pickProg.use(); 
    for(drawStyle d: target){
      passUniforms(&pickProg,&d.unfms);
      if (d.m_mesh) d.m_mesh->draw();
    }
  }

  //The default overriden case
  else {
    for (drawStyle d : target){
      if (d.prog){
        if (c_prog != d.prog){
          d.prog->use();
          c_prog = d.prog;
          //d.prog->setViewMatrix(currentProjViewMat);
        }
      }

      passUniforms(c_prog,&d.unfms);

      if (d.m_mesh){
        d.m_mesh->draw();
      }
    }
  }

}

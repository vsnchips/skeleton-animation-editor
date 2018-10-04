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


void app_renderer::pickDraw(std::vector<drawStyle> & t){

 pickProg.use();
    for(drawStyle d: t){
      passUniforms(&pickProg,&d.unfms);
      if (d.m_mesh && d.tag == "joint") d.m_mesh->draw();
    }

}

void app_renderer::execute(std::vector<drawStyle> & target){

  // Pick Preview
  if (previewPick){
    pickDraw(target);
  }

  //The default overriden case
  else {
    for (drawStyle d : target){
      if (d.prog){
        if (c_prog != d.prog){
          d.prog->use();
          c_prog = d.prog;
        }
      }

      passUniforms(c_prog,&d.unfms);

      if (d.m_mesh){
        if (d.mode > -1) d.m_mesh->draw(d.mode);
        else d.m_mesh->draw();
      }
    }
  }

}

int app_renderer::pickTest( std::vector<drawStyle> target, glm::vec2 &  m_mousePosition){

int pickedID = -1;
// Clear the back buffer
glClearColor(255, 255, 255, 1);
glClearDepth(1);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

pickDraw(target);

// Reading in after drawing
unsigned char pixel[4];
glReadPixels(m_mousePosition.x,
m_viewportSize.y - m_mousePosition.y, 1, 1,   GL_RGBA,   GL_UNSIGNED_BYTE,   &pixel);

float pickDepth; //might need the depth to find things;

glReadPixels(m_mousePosition.x,
m_viewportSize.y - m_mousePosition.y, 1, 1,   GL_DEPTH_BUFFER_BIT,   GL_FLOAT,   &pickDepth);

if (!(pixel[0]==255) || !(pixel[1]==255) || !(pixel[2]==255) ){

    pickedID = pixel[0] + pixel[1]*256 + pixel[2]*256*256;

    printf("RED %i\n", pixel[0]);
    printf("GREEN %i\n", pixel[1]);
    printf("BLUE %i\n", pixel[2]);

}

printf("Picked id %d\n", pickedID );
printf("Picked pickDepth %f\n", pickDepth );
return pickedID;

}

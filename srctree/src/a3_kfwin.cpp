
#include "includes-l1.hpp"
#include "a3.hpp"
#include "drawStyle.hpp"
// Keyframe window methods

using namespace std;
using namespace glm;

void a3_Application::kfwin_oncursor(double xpos, double ypos){


  // Make a vec2 with the current mouse position
  glm::vec2 currentMousePosition(xpos, ypos);
  // Get the difference from the previous mouse position
  glm::vec2 mousePositionDelta = currentMousePosition - m_kfMousePos;

  if (glm::length(mousePositionDelta)> 0) {
    if(m_mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]){
      if (pickKF >= 0){
      
      currentViewCurve->movePoint(pickKF,mousePositionDelta);
           
      }
   
    }
  }


}

void a3_Application::kfwin_onMouse(int button, int action, int mods){

    if (button == 0){
      if (action == GLFW_PRESS && currentViewCurve) {
        pickKF = a3_kf_renderer.pickTest( currentViewCurve->getStyle() , m_kfMousePos);
        clickon = pickKF > 0;
        printf("clickon kf %s\n" , clickon ? "true" : "false");
    }
      else {
      clickon = false;
      printf("unclick kf\n");

    }
  }
}

void a3_Application::kfwin_onkey(int key, int scancode, int action, int mods){

}

void a3_Application::kfwin_onscroll(double xoffset, double yoffset){

}

drawList a3_Application::testDrawList(cgra::Mesh * ctlMesh ){

  static float ys[] = {0.5, 1, -1, -0.5};

  mat4 proj(1);
  mat4 view(1);

  drawList dList; dList.clear();

  //Bezier Line
// Todo: get the line from the boneCurve

// drawList lineStyle = nowCurve->getStyle();
  //Controls
  const int degree = 5;
  float fstep =2./float(degree);
  for (int i=0; i< 5; i++){
    float x = i*fstep-1;
    float y = ys[i];

    drawStyle thisPt;

    //thisPt.prog = &m_program;
    vec2 pt(x,y);

    thisPt.m_mesh = ctlMesh;
    //thisPt.unfms.m4["projectionMat"] = proj;
    thisPt.unfms.m4["projectionMat"] = projectionMatrix;
    //thisPt.unfms.m4["viewMat"] = view;
    thisPt.unfms.m4["viewMat"] = viewMatrix;
    
    mat4 wm = translate( scale( mat4(), vec3(0.1)), vec3(x,y,0));
     thisPt.unfms.m4["modelMat"] = wm;
   // thisPt.unfms.m4["modelMat"] = mat4(1);

    dList.push_back(thisPt);

  }

  return dList;
}

void a3_Application::makeCurve(){}
void a3_Application::styleCurve(){

 // if (currentViewCurve){
//    vector<drawStyle> cs = currentViewCurve->getStyle();
//
   m_program.use();
   a3Renderer.c_prog = &m_program;
   a3_kf_renderer.c_prog = &m_program;
   drawList controls = testDrawList(&theAsfApp->m_jointMesh);

   //theAsfApp->m_jointMesh.draw();
   a3_kf_renderer.execute( controls );
//   a3Renderer.execute( theAsfApp->stylePack );
 
  //}

}




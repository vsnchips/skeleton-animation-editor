
#include "includes-l1.hpp"
#include "a3.hpp"

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
      //        click = true;
      //  fclick = glm::vec2(-1+2*m_kfMousePos.x/width, -1+2*m_kfMousePos.y/height);
      // glm::vec2 nowpos == glm::vec2(-1+2*currentMousePosition.x/width, -1+2*currentMousePosition.y/height);
      
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

void a3_Application::makeCurve(){}
void a3_Application::styleCurve(){

  if (currentViewCurve){
    vector<drawStyle> cs = currentViewCurve->getStyle();
   a3_kf_renderer.execute( cs );
 
  }

}





#include "includes-l1.hpp"
#include "a3.hpp"
#include "drawStyle.hpp"
// Keyframe window methods

using namespace std;
using namespace glm;

void a3_Application::kfWindowFresh(){

  
  int width, height;
   glfwGetFramebufferSize(m_window, &width, &height);
   m_kfWinSize=glm::vec2(width-50,height/3-50);

   glViewport(25, 25, width-50, height/3-50);
   glScissor(25, 25, width-50, height/3-50);

   glEnable(GL_SCISSOR_TEST);
   glClearColor(0.2,0.2,0.4, 1); // Clears the color to a dark blue
   glClearDepth(1); // Clears the depth buffer to it's maximum value
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //draw some beziers.
    styleCurve();
   
    glDisable(GL_SCISSOR_TEST);


}

void a3_Application::kfWindowPick(){

  freshEditBuff();
   
   // Create the draw region
   glViewport(25, 25, m_kfWinSize.x, m_kfWinSize.y);
   glScissor(25, 25, m_kfWinSize.x, m_kfWinSize.y);

   glEnable(GL_SCISSOR_TEST);
   glClearColor(1.,1.,1., 1); // Clears to white
   glClearDepth(1); // Clears the depth buffer to it's maximum value
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   a3Renderer.pickProg.setViewMatrix(viewMatrix);
   a3Renderer.pickProg.setProjectionMatrix(projectionMatrix);
   drawList controls = testDrawList(&theAsfApp->m_jointMesh);
                pickKF = a3Renderer.pickTest(controls,m_mousePosition);
                //pickKF = a3Renderer.pickTest(theAsfApp->stylePack,m_mousePosition);
                glfwSwapBuffers(m_window);
                a3Renderer.highLight = pickKF;

   glDisable(GL_SCISSOR_TEST);

  printf("picked Keyframe %d\n" , pickKF);

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

    vec2 pt(x,y);

    thisPt.m_mesh = ctlMesh;
    thisPt.unfms.i1["id"] = i+1; 
    thisPt.unfms.f3["ucol"] = vec3(0.5,0.5,0.8);
    //thisPt.unfms.m4["projectionMat"] = projectionMatrix;
   // thisPt.unfms.m4["viewMat"] = viewMatrix;
    
    mat4 wm = translate( scale( mat4(), vec3(0.1)), vec3(x,y,0));
    thisPt.unfms.m4["modelMat"] = wm;

    thisPt.tag="pickable";
    dList.push_back(thisPt);
  }

  return dList;
}

void a3_Application::makeCurve(){}


void a3_Application::styleCurve(){
   drawList controls = testDrawList(&theAsfApp->m_jointMesh);
   //a3_kf_renderer.c_prog = &m_program;
   //a3_kf_renderer.execute( controls );

   a3Renderer.c_prog = &m_program;
   a3Renderer.execute( controls );
}




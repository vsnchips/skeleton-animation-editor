

#include "includes-l1.hpp"
#include "a3.hpp"
#include "splineMath.hpp"
#include "drawStyle.hpp"

#include "boneCurve.hpp"

// Keyframe window methods

using namespace std;
using namespace glm;

void a3_Application::styleCurve(){
   drawList controls = testDrawList(&theAsfApp->m_jointMesh);

   kf_Renderer.highLight = theAsfApp-> focusIndex+1; 

   kf_Renderer.c_prog = &m_program;
   kf_Renderer.execute( controls );
}

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

<<<<<<< HEAD
   // Create the draw region
   glViewport(25, 25, m_kfWinSize.x, m_kfWinSize.y);
   glScissor(25, 25, m_kfWinSize.x, m_kfWinSize.y);
=======
    if (button == 0){
      if (action == GLFW_PRESS && currentViewCurve) {
        pickKF = a3_kf_renderer->pickTest( currentViewCurve->getStyle() , m_kfMousePos);
        clickon = pickKF > 0;
        printf("clickon kf %s\n" , clickon ? "true" : "false");
    }
      else {
      clickon = false;
      printf("unclick kf\n");
>>>>>>> 9a577229aa718f179264d1981593f53a65ac11fb

   glEnable(GL_SCISSOR_TEST);
   glClearColor(1.,1.,1., 1); // Clears to white
   glClearDepth(1); // Clears the depth buffer to it's maximum value
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   drawList controls = testDrawList(&theAsfApp->m_jointMesh);
    kf_Renderer.c_prog = &kf_Renderer.pickProg;
    pickKF = kf_Renderer.pickTest(controls,m_mousePosition);
    kf_Renderer.highLight = pickKF;
  // glfwSwapBuffers(m_window);

   glDisable(GL_SCISSOR_TEST);

  printf("picked Keyframe %d\n" , pickKF);

}


drawList a3_Application::testDrawList(cgra::Mesh * ctlMesh ){

  //Control Points

  boneCurve testBoneCurve;

  static float ys[] = {0.5, 1, -1, -0.5};
          vector<vec2> testCats; testCats.clear();
  testCats.push_back(vec2(-2,0.));
  testCats.push_back(vec2(-1,-0.5));
  testCats.push_back(vec2(0,0.5));
  testCats.push_back(vec2(1,0.5));
  testCats.push_back(vec2(2,-0.5));
  testCats.push_back(vec2(3,-0.5));
  testCats.push_back(vec2(4,0.5));
  testCats.push_back(vec2(5,0.));

  testBoneCurve.catreps =  testCats;

  vec2 sp = catSamp2D(theAsfApp->m_kf_play_pos, testCats);

  mat4 proj(1);
  mat4 view(1);

  drawList dList; dList.clear();
    
  drawStyle viewStyle;
  viewStyle.unfms.m4["viewMat"]=mat4(1);

  float asp = m_kfWinSize.x/m_kfWinSize.y;
  float invasp = 1/asp;
  viewStyle.unfms.m4["projectionMat"] = ortho(-2.f, 2.f, -2.f, 2.f,-100.f, 100.f);
//  dList.push_back(viewStyle);
  
  //Bezier Line
// Todo: get the line from the boneCurve
<<<<<<< HEAD
//
  drawList lineStyle = testBoneCurve.getStyle();

  dList.insert(dList.end(), lineStyle.begin(), lineStyle.end());

  drawStyle testPoint;
  
  testPoint.unfms.m4["modelMat"] = scale (translate( mat4(),
  vec3( sp.x , sp.y , 0)),
  vec3(0.5*invasp,0.2,0.1)) ;

  testPoint.m_mesh = ctlMesh;
  testPoint.unfms.f3["ucol"] = vec3(1,0,1);
  
  dList.push_back(testPoint);
  
//Controls
  const int degree = 5;
  float fstep =2./float(degree);
  for (int i=0; i< 8; i++){
    float x = testCats[i].x;
    float y = testCats[i].y;
=======

  //Controls
  const int degree = 5;
  float fstep = 2./float(degree);
  for (int i=0; i< 5; i++){
    float x = i*fstep-1;
    float y = ys[i];
>>>>>>> 9a577229aa718f179264d1981593f53a65ac11fb

    drawStyle thisPt;

    vec2 pt(x,y);

    thisPt.m_mesh = ctlMesh;
    thisPt.unfms.i1["id"] = i+1; 
    thisPt.unfms.f3["ucol"] = vec3(0.5,0.5,0.8);
    
    mat4 wm = scale (translate( mat4(), vec3(x,y,0)), vec3(0.5*invasp,0.2,0.1)) ;
    thisPt.unfms.m4["modelMat"] = wm;

    thisPt.tag="pickable";
    dList.push_back(thisPt);
  }

  return dList;
}

void a3_Application::makeCurve(){}
<<<<<<< HEAD
=======
void a3_Application::styleCurve(){

 // if (currentViewCurve){
//    vector<drawStyle> cs = currentViewCurve->getStyle();
//
   m_program_sliders.use();
   //drawList controls = testDrawList(&m_spheremesh);
   drawList controls = testDrawList(&theAsfApp->m_jointMesh);
   
   a3_kf_renderer->c_prog = &m_program_sliders;

   //theAsfApp->m_jointMesh.draw();
   a3_kf_renderer->execute( controls );
   m_spheremesh.draw(GL_TRIANGLES);
 
  //}

}

>>>>>>> 9a577229aa718f179264d1981593f53a65ac11fb



#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstring>

#include "includes-l1.hpp"
#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "a3.hpp"
#include "math.h"

void a3_Application::init(const char * skelfile) {

    theAsfApp= new asfApp(m_window);
    theAsfApp->init(skelfile);
    // Load the shader program
    // The use of CGRA_SRCDIR "/path/to/shader" is so you don't
    // have to run the program from a specific folder.
    m_program = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        //CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        //CGRA_SRCDIR "/res/shaders/lambert.fs.glsl");
        CGRA_SRCDIR "/res/shaders/simple.fs.glsl");


    // Create a view matrix that positions the camera
    // 10 units behind the object
    viewMatrix = glm::mat4 (1);
    viewMatrix[3] = glm::vec4(0, 0, -1, 1);
    m_program.setViewMatrix(viewMatrix);
    a3Renderer.pickProg.setViewMatrix(viewMatrix);

    xax = glm::vec3(1.,0.,0.);
    yax = glm::vec3(0.,1.,0.);
    zax = glm::vec3(0.,0.,1.);

    m_translation.z=-2.0f;

    printf("\nxax: %f,%f,%f",xax.x,xax.y,xax.z);
    printf("\nyax: %f,%f,%f",yax.x,yax.y,yax.z);
    printf("\nzax: %f,%f,%f",zax.x,zax.y,zax.z);


    // Create the cube mesh
    createCube();

    //Load the sphereobj;
    loadObj("res/models/sphere.obj",m_spheremesh);


//    printf("setting brush color uniform\n");
    GLfloat idColor[3];

    idColor[0] = 255;
    idColor[1] = 255;
    idColor[2] = 255;
//    idColor[3] = 1.0;
 //GLuint loc = glGetUniformLocation(
//    m_program.m_program, "ucol");
 //   glUniform3fv(loc, 1, idColor);
//    printf("brush color uniform set\n");

    triangleMode = GL_TRIANGLES;


}

void a3_Application::createCube() {
    /************************************************************
     * 2. Create a Mesh                                         *
     *                                                          *
     * Add the remaining triangles for the cube                 *
     ************************************************************/

    // Use the correct number of rows for the full
    // cube.
    cgra::Matrix<double> vertices(8, 3);
    cgra::Matrix<unsigned int> triangles(12, 3);

    vertices.setRow(0, {  1.0,  1.0,  1.0 });
    vertices.setRow(1, { -1.0, -1.0,  1.0 });
    vertices.setRow(2, {  1.0, -1.0,  1.0 });

    vertices.setRow(3, { -1.0, 1.0,  1.0 });
    vertices.setRow(4, { 1.0, 1.0,  -1.0 });
    vertices.setRow(5, { -1.0, -1.0,  -1.0 });

    vertices.setRow(6, { 1.0, -1.0,  -1.0 });
    vertices.setRow(7, { -1.0, 1.0,  -1.0 });

    // Remember to make sure that the order of the vertices
    // is counter-clockwise when looking at the front of the
    // triangle.
    triangles.setRow(0, { 0, 1, 2 });
    triangles.setRow(1, { 0, 3, 1 });
    triangles.setRow(2, { 4, 6, 5 });
    triangles.setRow(3, { 4, 5, 7 });
    triangles.setRow(4, { 0, 2, 6 });
    triangles.setRow(5, { 0, 6, 4 });
    triangles.setRow(6, { 3, 5, 1 });
    triangles.setRow(7, { 3, 7, 5 });
    triangles.setRow(8, { 0, 7, 3 });
    triangles.setRow(9, { 0, 4, 7 });
    triangles.setRow(10, { 2, 1, 5 });
    triangles.setRow(11, { 2, 5, 6 });

    m_mesh.maxdist = sqrt(3);
    m_mesh.setData(vertices, triangles);

}

void a3_Application::loadObj(const char *filename,cgra::Mesh &targetMesh) {
    cgra::Wavefront obj;
    // Wrap the loading in a try..catch block
    try {
        obj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << e.what() << "'" << std::endl;
        return;
    }

    /************************************************************
     * 2. Create a Mesh                                         *
     *                                                          *
     * Use the data in `obj` to create appropriately-sized      *
     * vertex and index matrices and fill them with data.       *
     *                                                          *
     * Assume that all the faces in the file are triangles.     *
     ************************************************************/

    // Replace these with appropriate values
    int numVertices  = obj.m_positions.size();
    int numTriangles = obj.m_faces.size();
    printf("\nVerts %u, Tris %u,\n", numVertices, numTriangles);
    printf("\n Vertex 0 : %lf %lf %lf\n", obj.position(10).x, obj.position(10).y, obj.position(10).z);

    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);


    std::cout << "\nFilling Verts\n" << std::endl;

        // Add each position to the vertices matrix
        for(int i = 1; i <= numVertices;i++){
            vertices.setRow(i-1,{obj.m_positions[i-1].x,obj.position(i).y,obj.position(i).z});
        }

    std::cout << "\nFilling Tris\n" << std::endl;
        // Add each triangle's indices to the triangles matrix
        // Remember that Wavefront files use indices that start at 1
        for(int i = 0; i < numTriangles;i++) triangles.setRow(i,{obj.m_faces[i].m_vertices[0].m_p-1,
                                                                 obj.m_faces[i].m_vertices[1].m_p-1,
                                                                 obj.m_faces[i].m_vertices[2].m_p-1});
    targetMesh.maxdist = obj.range;
    targetMesh.setData(vertices, triangles);



}

void a3_Application::drawScene() {

  glfwMakeContextCurrent(m_window);

      ImGui_ImplGlfwGL3_NewFrame();
      int width, height;
      glfwGetFramebufferSize(m_window, &width, &height);
      glViewport(0, 0, width, height);
      setWindowSize(width, height);
      glClearColor(0, 0, 0.1, 1); // Clears the color to a dark blue
      glClearDepth(1); // Clears the depth buffer to it's maximum value
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Create the GUI.
      // Note: this does not draw the GUI
      doGUI();


    // Calculate the aspect ratio of the viewport;
    // width / height
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    // Calculate the projection matrix with a field-of-view of 45 degrees
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);


    m_modelTransform = glm::mat4(1.0f);

    /************************************************************
     * 3. Manual Transforms                                     *
     *                                                          *
     * Use `m_translation`, `m_scale`, and `m_rotationMatrix`   *
     * to create the  `modelTransform` matrix.                  *
     * The following glm functions will be useful:              *
     *    `glm::translate`                                      *
     *    `glm::scale`                                          *
     ************************************************************/

    viewMatrix = glm::mat4(1);
    viewMatrix[3] = glm::vec4(0, 0, -1, 1);


    viewMatrix *= glm::translate(glm::mat4(),m_translation);
    viewMatrix *= glm::scale(m_modelTransform,glm::vec3(m_scale));
    m_rotationMatrix = glm::mat4(glm::vec4(xax,0),glm::vec4(yax,0),glm::vec4(zax,0),glm::vec4(0.f,0.f,0.f,1.f));
    viewMatrix *= m_rotationMatrix;

    // Draw the box
    m_program.use();


    a3Renderer.pickProg.setViewMatrix(viewMatrix);
    a3Renderer.pickProg.setProjectionMatrix(projectionMatrix);
    //a3Renderer.pickProg.setModelMatrix(m_modelTransform);
    m_program.setProjectionMatrix(projectionMatrix);
    m_program.setViewMatrix(viewMatrix);
    m_program.setModelMatrix(m_modelTransform);

  //Draw the skeleton

  theAsfApp -> showskel -> setProgram( m_program );
  theAsfApp -> updateScene();//  Draw The Skeleton
  //m_program.use();
  a3Renderer.execute(theAsfApp->stylePack);
   // Make sure that we're drawing with the correct
   // polygon mode
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   // Now we draw the GUI over the top of everything else
   ImGui::Render();
   // Finally, swap the front and back buffers.
   // We've been drawing to the back buffer so far, so this
   // makes it visible.
                   // Next frame we draw to the other buffer
   glfwSwapBuffers(m_window);
	
    
                
                
                
                
                
                
                // Keyframe Curve Window
    //
    if (keyframe_window){
    glfwMakeContextCurrent( keyframe_window);
      glClearColor(0, 0, 0.1, 1); // Clears the color to a dark blue
      glClearDepth(1); // Clears the depth buffer to it's maximum value
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     styleCurve() ;

    glfwSwapBuffers(keyframe_window);
    //draw some beziers.
    }

}

// Input Handlers

void a3_Application::onMouseButton(int button, int action, int) {

    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        if (button ==0){
            if( action == GLFW_PRESS) {

              glfwMakeContextCurrent(m_window);
    a3Renderer.pickProg.use();
    a3Renderer.pickProg.setViewMatrix(viewMatrix);
    a3Renderer.pickProg.setProjectionMatrix(projectionMatrix);
                pickID = a3Renderer.pickTest(theAsfApp->stylePack, m_mousePosition);
                clickon = pickID > 0;
                printf("clickon %s\n" , clickon ? "true" : "false");

                  if (clickon) { theAsfApp -> focusBone( pickID );}
            }
            else {clickon = false;
                printf("unclick\n");
            }
        }
        m_mouseButtonDown[button] = action == GLFW_PRESS;
    }
}

void a3_Application::onCursorPos(double xpos, double ypos) {
    /**********************************************************
     * 4. Interactive Transforms                              *
     *                                                        *
     * Change `translation`, `scale` and `rotation` based on  *
     * `mousePositionDelta`.                                  *
     **********************************************************/


    // Make a vec2 with the current mouse position
    glm::vec2 currentMousePosition(xpos, ypos);

    // Get the difference from the previous mouse position
    glm::vec2 mousePositionDelta = currentMousePosition - m_mousePosition;

    if (glm::length(mousePositionDelta)>0){


        static bool click=false;
        static glm::vec3 sxa, sya, sza;
        static glm::vec2 fclick;


       if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]) {

           static int width, height;
           glfwGetWindowSize(m_window, &width, &height);

           int size = glm::min(width,height);

        if (pickID == -1){

           click = true;

               fclick = glm::vec2(-1+2*m_mousePosition.x/width,-1+2*m_mousePosition.y/height);
               sxa = xax;
               sya = yax;
               sza = zax;

            glm::vec2 nowpos = glm::vec2(-1+2*currentMousePosition.x/width,-1+2*currentMousePosition.y/height);

            if (height>width) {nowpos.y *= height/width; fclick.y *= height/width;}
            else {nowpos.y *= width/height; fclick.y *= width/height;}

            nowpos.x *= 0.8;
            nowpos.y *=0.8;
            fclick.x *= 0.8;
            fclick.y *=0.8;

           //Transform the coords to match the target object
           //
           
            nowpos.x*=-m_translation.z;
            nowpos.y*=-m_translation.z;
            fclick.x*=-m_translation.z;
            fclick.y*=-m_translation.z;
            nowpos.x = nowpos.x - m_translation.x;
            fclick.x = fclick.x - m_translation.x;
            nowpos.y = nowpos.y + m_translation.y;
            fclick.y = fclick.y + m_translation.y;

            nowpos.x /= m_mesh.maxdist;
            nowpos.y /= m_mesh.maxdist;

            fclick.x /= m_mesh.maxdist;
            fclick.y /= m_mesh.maxdist;

            nowpos.x /=m_scale;
            nowpos.y /=m_scale;

            fclick.x /=m_scale;
            fclick.y /=m_scale;


            if (glm::length(fclick) > 1) fclick = glm::normalize(fclick);
            if (glm::length(nowpos) > 1) nowpos = glm::normalize(nowpos);

            //vectorise Arc Points
            printf("\ncurrentMouse: %lf, %lf",fclick.x,fclick.y);
            glm::vec4 apA = glm::vec4(fclick.x,-fclick.y,glm::cos(glm::asin(glm::min(glm::length(fclick),0.99999f))),1.);
            glm::vec4 apB = glm::vec4(nowpos.x,-nowpos.y,glm::cos(glm::asin(glm::min(glm::length(nowpos),0.99999f))),1.);


            glm::vec3 apA3 = glm::vec3(apA.x,apA.y,apA.z);
            glm::vec3 apB3 = glm::vec3(apB.x,apB.y,apB.z);
            float t = glm::acos(glm::dot(glm::normalize(apA3),glm::normalize(apB3)));

            if (isnan(t) ) {printf("  T NAN !!!");
                t = 0.f;
                apA=glm::vec4(1.);
                apB=glm::vec4(1.);
                apA3=glm::vec3(1.,0.,0);
                apB3=glm::vec3(0.,0.,1.);
            }

            glm::vec3 n = glm::cross(apA3,apB3);
            xax= glm::rotate(sxa,t,n);
            yax= glm::rotate(sya,t,n);
            zax= glm::rotate(sza,t,n);

            //Transform modified by arcball twiddling
            //This codes updates the polar coords:

            //1.Get Latitude and Longtitude
            polarrotation.x = glm::acos(glm::dot(glm::vec3(0.,0.,1.),zax)); // -pi<Latitude<=pi ;

            polarrotation.y = glm::atan(zax.y,zax.x);

            //2. Get the normal of current and reference Z basevecs
            glm::vec3 tiltnorm = glm::cross(zax,glm::vec3(0.,0.,1.));
            glm::vec3 uprightX = glm::rotate(xax,polarrotation.x,tiltnorm);
            glm::vec3 uprightY = glm::rotate(yax,polarrotation.x,tiltnorm);

            // Get the Z angle
            polarrotation.z = glm::acos(glm::dot(uprightX,glm::vec3(1.0f,0.f,0.f)));
            }  else {

              
                }
            }

        }



     if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_MIDDLE]) {
         static int width, height;
         glfwGetWindowSize(m_window, &width, &height);
         int size = glm::max(width,height);
         glm::vec2 shift = glm::vec2((m_translation.z)*-mousePositionDelta.x/size,(m_translation.z)*mousePositionDelta.y/size);
         m_translation = glm::vec3(m_translation.x+shift.x,m_translation.y+shift.y,m_translation.z);


    }if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_RIGHT]) {
         //
         m_scale += glm::max(m_scale,0.1f)*0.1*-mousePositionDelta.y;
    }
     // Update the mouse position to the current one
     m_mousePosition = currentMousePosition;
}


void a3_Application::onKey(int key, int scancode, int action, int mods) {
    // `(void)foo` suppresses unused variable warnings
    if(key == GLFW_KEY_X && action == GLFW_PRESS) //cycle axes
    {
    }

    if(key == GLFW_KEY_A && action == GLFW_PRESS) //cycle axes
    {
      theAsfApp->m_play = !theAsfApp->m_play;
    }

     if(key == GLFW_KEY_N && action == GLFW_PRESS) //cycle axes
    {
      theAsfApp->nextPose();
    }

     if(key == GLFW_KEY_P && action == GLFW_PRESS) //cycle axes
    {
      theAsfApp->prevPose();
    }

    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
}

void a3_Application::onScroll(double xoffset, double yoffset) {
    // `(void)foo` suppresses unused variable warnings
    (void)xoffset;
    (void)yoffset;
}


// void frameToPose(){
//  pose newPose(asfApp.getPose());
//
// }
//
// 

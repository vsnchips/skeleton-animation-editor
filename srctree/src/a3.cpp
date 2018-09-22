#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstring>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "a3.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "math.h"


void a3_Application::init() {

    theAsfApp= new asfApp(m_window);
    theAsfApp->init();
    // Load the shader program
    // The use of CGRA_SRCDIR "/path/to/shader" is so you don't
    // have to run the program from a specific folder.
    m_program = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        //CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        //CGRA_SRCDIR "/res/shaders/lambert.fs.glsl");
        CGRA_SRCDIR "/res/shaders/lambert.fs.glsl");


    // Create a view matrix that positions the camera
    // 10 units behind the object
    glm::mat4 viewMatrix(1);
    viewMatrix[3] = glm::vec4(0, 0, -1, 1);
    m_program.setViewMatrix(viewMatrix);

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


    printf("setting brush color uniform\n");
    GLfloat idColor[4];

    idColor[0] = 255;
    idColor[1] = 255;
    idColor[2] = 255;
    idColor[3] = 1.0;
    GLuint loc = glGetUniformLocation(
    m_program.m_program, "gColor");
    glUniform4fv(loc, 1, idColor);
    printf("brush color uniform set\n");

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


    // Calculate the aspect ratio of the viewport;
    // width / height
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    // Calculate the projection matrix with a field-of-view of 45 degrees
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);


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

    m_modelTransform *= glm::translate(glm::mat4(),m_translation);
    m_modelTransform *= glm::scale(m_modelTransform,glm::vec3(m_scale));
    m_rotationMatrix = glm::mat4(glm::vec4(xax,0),glm::vec4(yax,0),glm::vec4(zax,0),glm::vec4(0.f,0.f,0.f,1.f));
    m_modelTransform *= m_rotationMatrix;


    glm::mat4 viewMatrix(1);
    viewMatrix[3] = glm::vec4(0, 0, -1, 1);

    //Draw the Lattice
    // todo: see theLattice class for line drawing code
    //
    // theLattice.latProgram.use();
    //use this space for drawing wireframes
    //
    // Draw the mesh
    m_program.use();

    GLfloat idColor[4];   //WHITE
    idColor[0] = 255;
    idColor[1] = 255;
    idColor[2] = 255;
    idColor[3] = 1.0;
   /* GLuint loc = glGetUniformLocation(
    m_program.m_program, "gColor");
    glUniform4fv(loc, 1, idColor);
*/
    m_program.setViewMatrix(viewMatrix);
    m_program.setProjectionMatrix(projectionMatrix);
    m_program.setModelMatrix(m_modelTransform);
    m_mesh.draw(GL_TRIANGLES);


}

void a3_Application::doGUI() {
    ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");

    /************************************************************
     *                                                          *
     * 2. Load an .obj file                                     *
     *                                                          *
     * Add an input for a filename.                             *
     *                                                          *
     ************************************************************
     *                                                          *
     * 3. Manual Transforms                                     *
     *                                                          *
     * Create inputs for controlling translation, scale and     *
     * rotation.                                                *
     *
     ************************************************************
     */

    ImGui::SliderFloat3("Translate",&m_translation[0],-20.0f,20.0f, "%.5f",1.5f);
    ImGui::SliderFloat("Scale",&m_scale,0,5.0f, "%.5f", 2.5f);
    if(ImGui::SliderFloat3("Rotate",&polarrotation[0],-M_PI,M_PI, "%.5f", 1.0f)){
        // User's spun the globe
        // Find the resulting matrix!

        //1. Transform the Z/north pole, X/west, and Y/celestial vectors via the input lat/long TODO: How do i get this into a mat3x3?
     if ( polarrotation.x == 0 ){
         zax = glm::vec3(0,0,1);
         yax = glm::vec3(0,1,0);
         xax = glm::vec3(1,0,0);
     }
     else {
         //fix for negative latitudes:
         float polx,poly;
         if (polarrotation.x < 0){
             polx =-polarrotation.x;
             poly = polarrotation.y + M_PI;
         } else {
             polx = polarrotation.x;
             poly = polarrotation.y;
         }

         zax = glm::rotate(
                    (glm::rotate(glm::vec3(0.,0.,1.),polx,glm::vec3(0.,1.,0.))) // tilt it on Y over to X to latitude
                    ,poly, glm::vec3(0.,0.,1.));  // spin it on true Zorth to longtitude

        //2.Find the normal and angle between Zorth and the new Z, and apply the same rotation to Xwest and YCelestial
        glm::vec3 tnorm = glm::cross(glm::vec3(0.,0.,1.),zax);
        yax = glm::rotate(glm::vec3(0.,1.,0.),polx,tnorm);
        xax = glm::rotate(glm::vec3(1.,0.,0.),polx,tnorm);
      }
        //3. Rotate X and Y around the tilted Z pole/
        yax = glm::rotate(yax, polarrotation.z, zax);
        xax = glm::rotate(xax, polarrotation.z, zax);

    };

    ImGui::End();

    ImGui::Begin("Shader Controls");
       if (ImGui::Button("Reload Shader")){/*
         m_program = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/warpthedragon.vs.glsl",
        //CGRA_SRCDIR "/res/shaders/lambert.fs.glsl");
        CGRA_SRCDIR "/res/shaders/lambert.fs.glsl");

         GLint *params;
         //glGetShaderiv(GL_COMPILE_STATUS);
         //printf("%s shader compilation\n", (params == GL_TRUE) ? "Succeeded" : "FAILED" );

         glGetProgramiv(m_program.m_program,GL_LINK_STATUS,params);

         printf("%s program linking\n", (*params == GL_TRUE) ? "Succeeded" : "FAILED" );
         //update uniforms
         //
*/
         }


    ImGui::Begin("Gui Tweaking");
    //    ImGui::SliderFloat("Handle Size", &theSkeleton.jointSize, 0, 1);
    //
    ImGui::End();



    /*
     ************************************************************
     *                                                          *
     * 5. Add a checkbox for rendering the object in wireframe  *
     *  mode.                                                   *
     ************************************************************/

    static bool wireframe;
    if(ImGui::Checkbox("Draw Wireframe",&wireframe)) {
        m_mesh.setDrawWireframe(wireframe);
    }

    //debugging stuff:

    ImGui::Text("tricount :%d" , m_mesh.m_indices.size()/3);
    ImGui::Text("vertcount : %d" , m_mesh.m_vertices.size());

    ImGui::End();
}


// Input Handlers

void a3_Application::onMouseButton(int button, int action, int) {

    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        if (button ==0){
            if( action == GLFW_PRESS) {
                pickID = pickTest();
                clickon = pickID > 0;
                printf("clickon %s\n" , clickon ? "true" : "false");
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
/* picking code
                if(pickID>=0 && pickID < theLattice.getFullSize()){
                    theLattice.getByID(pickID).move(glm::vec2(mousePositionDelta.x/height,mousePositionDelta.y/height),m_rotationMatrix,m_scale,pickDepth);
                    theLattice.vao.setRow(pickID,{  theLattice.getByID(pickID).p.x  ,
                                                theLattice.getByID(pickID).p.y  ,
                                                theLattice.getByID(pickID).p.z });
                    theLattice.setMesh();
                    theLattice.VSArraytoUniform(m_program);
                    if(!theLattice.GPUwarp)theLattice.makeWarpMesh(m_mesh);
                    */
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


int a3_Application::pickTest(){

int pickedID = -1;
// Clear the back buffer
glClearColor(255, 255, 255, 1);
glClearDepth(1);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//Draw the pickable elements
/*theLattice.drawForPick(theLattice.latProgram,
                                        m_modelTransform,
                                        m_rotationMatrix,
                                        glm::translate(glm::mat4(),m_translation),
                                        m_scale);
*/

// Reading in after drawing
unsigned char pixel[4];
glReadPixels(m_mousePosition.x,
m_viewportSize.y - m_mousePosition.y, 1, 1,   GL_RGBA,   GL_UNSIGNED_BYTE,   &pixel);
glReadPixels(m_mousePosition.x,
m_viewportSize.y - m_mousePosition.y, 1, 1,   GL_DEPTH_BUFFER_BIT,   GL_FLOAT,   &pickDepth);

if (!(pixel[0]==255) || !(pixel[1]==255) || !(pixel[2]==255) ){

    pickedID = pixel[0] + pixel[1]*256 + pixel[2]*256*256;


    printf("RED %i\n", pixel[0]);
    printf("GREEN %i\n", pixel[1]);
    printf("BLUE %i\n", pixel[2]);

}

m_program.use();

//glfwSwapBuffers(m_window);
printf("Picked id %d\n", pickedID );
printf("Picked pickDepth %f\n", pickDepth );
return pickedID;

}

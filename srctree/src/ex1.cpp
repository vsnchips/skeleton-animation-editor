#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstring>


#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "ex1.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "math.h"
#include "../include/nfd.h"

void Application::loadSkeleton(){
     nfdchar_t * skelFile;

     NFD_OpenDialog( "*", "", &skelFile);
     printf("\nloading %s\n",skelFile);
     //showskel = (Skeleton *) malloc(sizeof(Skeleton));
     //Skeleton newskel = Skeleton(skelFile);
     showskel = new Skeleton(skelFile);
//     showskel = &newskel;
     showskel->defaultBoneMesh(&m_mesh);
     //showskel->m_program = &m_program;
     showskel->setProgram(m_program);
     skelload = true;

}
void Application::init() {
    // Load the shader rogram
    // The use of CGRA_SRCDIR "/path/to/shader" is so you don't
    // have to run the program from a specific folder.
    m_program = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
        CGRA_SRCDIR "/res/shaders/simple.fs.glsl");

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
}

void Application::createCube() {
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

void Application::loadObj(const char *filename) {
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
    m_mesh.maxdist = obj.range;
    m_mesh.setData(vertices, triangles);
}

void Application::drawScene() {
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    //m_mesh.draw();
    
    if( skelload && showskel -> m_bones.size() > 0){
    showskel->m_program->setProjectionMatrix(projectionMatrix);
	printf("there are %d bones\n", showskel->m_bones.size());
	    showskel->renderSkeleton( & m_mesh );
    }

}

void renderBone(bone b){
    
}


void Application::doGUI() {
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
		

    if(ImGui::Button("Load A Skeleton")){
	    loadSkeleton();
    }


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

    // MESH LOADING:

    static char dragon[] = "res/models/dragon.obj";

    static char path[256];

    if (std::strlen(path)<1) std::strcpy(path,dragon);

    (ImGui::InputText("Load *.OBJ",path, 256));

    if(ImGui::Button("Load File")){

        FILE * file = fopen(path, "r");
        if( file == NULL ){
            printf("Impossible to open the file !\n");
            //return false;
        }else {
            printf("Loading %s \n", path);

            loadObj(path);

            // The CGRA wavefront loader wasnt working for me

            // So I wrote this one:
            /*
            std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
            std::vector< double > temp_vertices;
            std::vector< double > temp_uvs;
            std::vector< double > temp_normals;

            float farvert=0; //get the furtherest vertex

            while( 1 ){

                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                    break;

            if ( strcmp( lineHeader, "v" ) == 0 ){
                float vertexx;
                float vertexy;
                float vertexz;
                fscanf(file, "%f %f %f\n", &vertexx, &vertexy, &vertexz );
                temp_vertices.push_back(vertexx);
                temp_vertices.push_back(vertexy);
                temp_vertices.push_back(vertexz);

                float len = glm::length(glm::vec3(vertexx,vertexy,vertexz));
                farvert = len>farvert? len : farvert;

            }else if ( strcmp( lineHeader, "vt" ) == 0 ){
                float uvx;
                float uvy;
                fscanf(file, "%f %f\n", &uvx, &uvy );
                temp_uvs.push_back(uvx);
                temp_uvs.push_back(uvy);
            }else if ( strcmp( lineHeader, "vn" ) == 0 ){
                float normalx;
                float normaly;
                float normalz;
                fscanf(file, "%f %f %f\n", &normalx, &normaly, &normalz );
                temp_normals.push_back(normalx);
                temp_normals.push_back(normaly);
                temp_normals.push_back(normalz);

            }else if ( strcmp( lineHeader, "f" ) == 0 ){
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                //int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                int matches = fscanf(file, "%u %u %u\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
                if (matches != 3){
                    printf("Cant read this .obj");
                   // return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);

            }


        }

            cgra::Matrix<double> verts(temp_vertices.size()/3,3);
            for(unsigned int i =0; i < temp_vertices.size()/3; i++) verts.setRow(i,{temp_vertices[i*3],temp_vertices[i*3+1],temp_vertices[i*3+2]});

            cgra::Matrix<unsigned int> faces(vertexIndices.size()/3,3);
            for(unsigned int i=0; i< vertexIndices.size()/3;i++) faces.setRow(i,{vertexIndices[i*3]-1,vertexIndices[i*3+1]-1,vertexIndices[i*3+2]-1});


            int numVertices  = temp_vertices.size()/3;
            int numTriangles = vertexIndices.size()/3;
            printf("Verts %u, Tris %u,\n", numVertices, numTriangles);

     m_mesh.maxdist = farvert;
     m_mesh.setData(verts,faces);*/

     } //endif loading
    }//endif textinput

    if(ImGui::Button("Load Cube")) createCube();

    //debugging stuff:

    ImGui::Text("tricount :%d" , m_mesh.m_indices.size()/3);
    ImGui::Text("vertcount : %d" , m_mesh.m_vertices.size());

    ImGui::End();
}


// Input Handlers

void Application::onMouseButton(int button, int action, int) {
    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        m_mouseButtonDown[button] = action == GLFW_PRESS;
    }
}

void Application::onCursorPos(double xpos, double ypos) {
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
            /*
            nowpos.x -= m_translation.x/(-m_translation.z);
            nowpos.y -= m_translation.y/(-m_translation.z);
            fclick.x -= m_translation.x/(-m_translation.z);
            fclick.y -= m_translation.y/(-m_translation.z);*/

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
}

void Application::onKey(int key, int scancode, int action, int mods) {
    // `(void)foo` suppresses unused variable warnings
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
}

void Application::onScroll(double xoffset, double yoffset) {
    // `(void)foo` suppresses unused variable warnings
    (void)xoffset;
    (void)yoffset;

}






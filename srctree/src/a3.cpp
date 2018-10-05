#include "a3.hpp"

void a3_Application::init(const char * skelfile) {

    theAsfApp= new asfApp(m_window);
    theAsfApp->init(skelfile);
    // Load the shader program
    // The use of CGRA_SRCDIR "/path/to/shader" is so you don't
    // have to run the program from a specific folder
    ///
    
    m_program = cgra::Program::load_program(
        CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
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

}

     //* 2. Create a Mesh                                         *
void a3_Application::loadObj(const char *filename,cgra::Mesh &targetMesh) {
    cgra::Wavefront obj;
    // Wrap the loading in a try..catch block
    try {
        obj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << e.what() << "'" << std::endl;
        return;
    }


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


void a3_Application::freshEditBuff(){

      int width, height;
      glfwGetFramebufferSize(m_window, &width, &height);
      glViewport(0, 0, width, height);
      setWindowSize(width, height);
      glClearColor(0, 0, 0.1, 1); // Clears the color to a dark blue
      glClearDepth(1); // Clears the depth buffer to it's maximum value
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void a3_Application::drawScene() {
    
    glfwMakeContextCurrent(m_window);
    freshEditBuff();

    //Projection Setup
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    // Calculate the projection matrix with a field-of-view of 45 degrees
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    // View Transforms
    m_modelTransform = glm::mat4(1.0f);
    viewMatrix = glm::mat4(1);
    viewMatrix[3] = glm::vec4(0, 0, -1, 1);

    viewMatrix *= glm::translate(glm::mat4(),m_translation);
    viewMatrix *= glm::scale(m_modelTransform,glm::vec3(m_scale));
    m_rotationMatrix = glm::mat4(glm::vec4(xax,0),glm::vec4(yax,0),glm::vec4(zax,0),glm::vec4(0.f,0.f,0.f,1.f));
    viewMatrix *= m_rotationMatrix;

    // Draw the skel
    m_program.use();
    
    a3Renderer.pickProg.setProjectionMatrix(projectionMatrix);
    a3Renderer.pickProg.setViewMatrix(viewMatrix);

    kf_Renderer.pickProg.setProjectionMatrix(projectionMatrix);
    kf_Renderer.pickProg.setViewMatrix(viewMatrix);
    
    m_program.setProjectionMatrix(projectionMatrix);
    m_program.setViewMatrix(viewMatrix);

  //Draw the skeleton

  theAsfApp -> showskel -> setProgram( m_program );
  theAsfApp -> updateScene();//  Draw The Skeleton
  
   a3Renderer.execute(theAsfApp->stylePack);
   
 
    // Keyframe Curve Window
    //
    if(kf_window_see){
      kfWindowFresh();
    }
               
  // Note: this does not draw the GUI
  ImGui_ImplGlfwGL3_NewFrame();
  doGUI();
  ImGui::Render();

//  if (!mouseDown)
    glfwSwapBuffers(m_window);

  freshEditBuff();// reset the Viewport transform;

}

// void frameToPose(){
//  pose newPose(asfApp.getPose());
//
// }
//
// 

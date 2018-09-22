#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstring>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "asf.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "math.h"
#include "../include/nfd.h"

#include <map>
#include <string>


using namespace std;

void asfApp::nextPose(){ switchPose(1);}
void asfApp::prevPose(){ switchPose(-1);}

void asfApp::switchPose(int dir){

	if (skelload){
	static vector<frame> poses; poses.clear();
        poses.push_back(sittingPose);
       	poses.push_back(guitarPose);
       	poses.push_back(walkingPose);

	static int f = 0;
	f += dir;
  int POSE_COUNT = 3;
	f = f % POSE_COUNT;

	showskel -> applyPose(&(poses[f]));

		//showkel -> cylcePose();

	}else{printf("no skeleton!a\n");}
}


void asfApp::loadSkeleton(){

     nfdchar_t * skelFile;

     NFD_OpenDialog( "*", "", &skelFile);
     printf("\nloading %s\n",skelFile);
     showskel = new Skeleton(skelFile); //hmmmm.. malloc perhaps?
     showskel->setProgram(m_program);
     showskel->m_bonemesh = &m_mesh;
     showskel->m_jointmesh = &m_jointMesh;
     skelload = true;



}

// TODO: put this in a lib or something. git it outa here!
// Helper method for retreiving and trimming the next line in a file.
// You should not need to modify this method.
namespace {
	string nextLineTrimmed(istream &file) {
		// Pull out line from file
		string line;
		getline(file, line);
		// Remove leading and trailing whitespace and comments
		size_t i = line.find_first_not_of(" \t\r\n");
		if (i != string::npos) {
			if (line[i] != '#') {
				return line.substr(i, line.find_last_not_of(" \t\r\n") - i + 1);
			}
		}
		return "";
	}
}


void asfApp::loadAnimation(){

     nfdchar_t * aniFile;

     NFD_OpenDialog( "*", "", &aniFile);
     printf("\nloading %s\n",aniFile);

    ifstream amcStream(aniFile);
    if (!amcStream.is_open()) {
    	printf("Cant open amc!\n");
    } else{

	//construct a clip
	theClip.clear();
	int cfnum = 0;

    while (amcStream.good()){
        string line = nextLineTrimmed(amcStream);
	if (line.empty() || line[0] == '#')
		continue;
	else if (line[0] == ':') {
	  //something something fully specified
	  //something something degrees
	}
   	else if (isdigit(line[0])){
		cfnum = atoi(&line[0]);
		if (theClip.size()<cfnum) {
		frame newframe; newframe.clear();
		theClip.push_back(newframe);
		}
	}
	else{
	//read the rotation in
		string thebone;
		istringstream lstream(line);
		lstream >> thebone;
		// float vec
		vector<float> rots;
		rots.clear();
		string num = "";
	 	while (lstream >> num){
			rots.push_back(stof(num));
			num="";
		}//got vector now
		theClip[cfnum-1][ thebone ] = rots; //copy the vector to the frame
	//breakpoint here
	printf("frame one:");

	for (auto const& x : theClip[0])
	{
		std::cout << x.first  // string (key)
			<< ':'
		//	<< x.second // string's value
			<< std::endl ;
	}
	}
    }
    }

	m_play=true;
}

void asfApp::play(){
	m_play = true;
}
void asfApp::pause(){
	m_play = false;
}

void asfApp::init() {
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

    m_translation.z=-0.0f;

    printf("\nxax: %f,%f,%f",xax.x,xax.y,xax.z);
    printf("\nyax: %f,%f,%f",yax.x,yax.y,yax.z);
    printf("\nzax: %f,%f,%f",zax.x,zax.y,zax.z);
    // Create the cube mesh
    createCube();

    static char pole[] = "../srctree/res/models/zpole.obj";
    m_mesh = loadObj(pole);
    static char sphere[] = "../srctree/res/models/sphere.obj";
    m_jointMesh = loadObj(sphere);

    loadSkeleton();

    sittingPose["lfemur"] = {-90,30,-10};
    sittingPose["rfemur"] = {-90,-30,10};
    sittingPose["ltibia"] = {100,10,-0};
    sittingPose["rtibia"] = {100,-10,0};
    sittingPose["lhumerus"] = {30,0,30};
    sittingPose["rhumerus"] = {-30,0,-30};
    sittingPose["lradius"] = {0,0.0};
    sittingPose["rradius"] = {0,0.0};

    guitarPose["lfemur"] = {-90,45,-10};
    guitarPose["rfemur"] = {-90,-45,10};
    guitarPose["ltibia"] = {160,10,-0};
    guitarPose["rtibia"] = {160,-10,0};
    guitarPose["lhumerus"] = {-20,0,30};
    guitarPose["rhumerus"] = {30,30,6};
    guitarPose["lradius"] = {90,0,0};
    guitarPose["rradius"] = {0,0.-0};
    guitarPose["rwrist"] = {40,0,0};
    guitarPose["lwrist"] = {-10,0,90};

    walkingPose["lfemur"] = {10,30,-10};
    walkingPose["rfemur"] = {-20,-30,10};
    walkingPose["ltibia"] = {20,10,-0};
    walkingPose["rtibia"] = {15,-10,0};
    walkingPose["lfoot"] = {0,0,-20};
    walkingPose["rfoot"] = {0,0,20};
    walkingPose["lhumerus"] = {30,-50,10};
    walkingPose["rhumerus"] = {-60,-30,-0};
    walkingPose["lradius"] = {50,45,45};
    walkingPose["rradius"] = {45,30,-45};



}

void asfApp::createCube() {
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

cgra::Mesh asfApp::loadObj(const char *filename) {

    cgra::Mesh newMesh;

    cgra::Wavefront obj;
    // Wrap the loading in a try..catch block
    try {
        obj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << e.what() << "'" << std::endl;
        return newMesh;
    }
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
    newMesh.maxdist = obj.range;
    newMesh.setData(vertices, triangles);

    return newMesh;
}

void asfApp::updateScene() {

stylePack.clear();

//updates
if (skelload && m_play){
	  m_play_pos += m_speed * 0.0002; showskel-> applyFrame( theClip, m_play_pos);
	}

//Deprecated draw stuff
	float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    // Create a view matrix that positions the camera
    // 10 units behind the object
    glm::mat4 viewMatrix(1);
    viewMatrix[3] = glm::vec4(0, 0, -10, 1);//translate the view
    viewMatrix *= glm::scale(viewMatrix,glm::vec3(m_scale));//zoom rel origin
    m_rotationMatrix = glm::mat4(glm::vec4(xax,0),glm::vec4(yax,0),glm::vec4(zax,0),glm::vec4(0.f,0.f,0.f,1.f));
     viewMatrix *= m_rotationMatrix;
    viewMatrix *= glm::translate(glm::mat4(),m_translation);
    m_program.setViewMatrix(viewMatrix);

    if( skelload && showskel -> m_bones.size() > 0){
    showskel->m_program->setProjectionMatrix(projectionMatrix);
//	printf("there are %d bones\n", showskel->m_bones.size());
	   stylePack = *showskel->renderSkeleton( & m_mesh , tether);
    }

}

void asfApp::doGUI() {

    // --- Clip Controls
    ImGui::SetNextWindowSize(ImVec2(500, 50), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");
    if(ImGui::SliderFloat("Position", &m_play_pos, 0.f, 1.f, "%.5f", 1.0f)){
    	showskel->applyFrame(theClip,m_play_pos);
    }

    if(ImGui::Button("Load A Clip")){
	    loadAnimation();
    }

    if(ImGui::Button("Play ")){
	    play();
    }

   if(ImGui::Button("Pause")){
	    pause();
    }

    if(ImGui::Button("Rewind")){
	    m_play_pos=0;
    }
    if(ImGui::Button(" Next Pose ")){
	   switchPose(1) ;
    }


   ImGui::Checkbox("Tethered Root",&tether);

    ImGui::SliderFloat("Speed",&m_speed, -5.f,5.f,"%.5f",1.0f);

    ImGui::End();
    // ---

    // --- Camera Controls
    ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");

   //Camera
    ImGui::SliderFloat3("Translate",&m_translation[0],-20.0f,20.0f, "%.5f",1.5f);
    if(ImGui::SliderFloat("Scale",&m_scale,0,100.0f, "%.5f", 5.f)){
    	if (skelload) showskel->axisSize = 1/m_scale;
    }

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
     *************************************************:516
		 ***********/

    // Mesh / Geometry / Skeleton / Character / Assets
    // controls
    if(ImGui::Button("Load A Skeleton")){
	    loadSkeleton();
    }


    static bool wireframe;
    if(ImGui::Checkbox("Draw Wireframe",&wireframe)) {
        m_mesh.setDrawWireframe(wireframe);
    }

    // MESH LOADING:/

    static char pole[] = "../srctree/res/models/zpole.obj";

    static char path[256];

    if (std::strlen(path)<1) std::strcpy(path,pole);

    (ImGui::InputText("Load *.OBJ",path, 256));

    if(ImGui::Button("Load File")){

        FILE * file = fopen(path, "r");
        if( file == NULL ){
            printf("Impossible to open the file !\n");
            //return false;
        }else {
            printf("Loading %s \n", path);

            m_mesh = loadObj(path);

     } //endif loading
    }//endif textinput

    if(ImGui::Button("Load Cube")) createCube();

    //debugging stuff:

    ImGui::Text("tricount :%d" , m_mesh.m_indices.size()/3);
    ImGui::Text("vertcount : %d" , m_mesh.m_vertices.size());

    ImGui::End();
}


// Input Handlers

void asfApp::onMouseButton(int button, int action, int) {
    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        m_mouseButtonDown[button] = action == GLFW_PRESS;
    }
}

void asfApp::onCursorPos(double xpos, double ypos) {
  }

void asfApp::onKey(int key, int scancode, int action, int mods) {
    // `(void)foo` suppresses unused variable warnings
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;

    if (key == GLFW_KEY_P && action == GLFW_PRESS ){
	    prevPose();
}
    if (key == GLFW_KEY_N && action == GLFW_PRESS ){
	    nextPose();
    }
}

void asfApp::onScroll(double xoffset, double yoffset) {
    // `(void)foo` suppresses unused variable warnings
    (void)xoffset;
    (void)yoffset;

}

frame asfApp::getPose(){

frame saveFrame;
if (skelload == true) {
  saveFrame = showskel->makeFrame();
} else {  
  cout << (" No skeleton is posing!");
}
return saveFrame;

}

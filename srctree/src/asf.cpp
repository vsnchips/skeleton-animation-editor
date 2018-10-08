#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cstring>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "math.h"
#include "../include/nfd.h"

#include <map>
#include <string>

#include "asf.hpp"

using namespace std;
using namespace glm;


//Pose Management Functions
void asfApp::nextPose(){ switchPose(1);}
void asfApp::prevPose(){ switchPose(-1);}

void asfApp::removePose(){
  removePose(focusIndex);
}

void asfApp::removePose(int focus){

  if (workPoses.size() > 0)
  workPoses.erase(workPoses.begin()+focus);

}
void asfApp::switchPose(int dir){    //Focuses a pose and sets the skeleton to match it.

  if (skelload){
    static vector<frame> poses; poses.clear();
    poses.push_back(sittingPose);
    poses.push_back(guitarPose);
    poses.push_back(walkingPose);

    static int f = 0;
    f += dir;
    int POSE_COUNT = workPoses.size();
    f = float(glm::mod(float(f), float(POSE_COUNT)));
    if (POSE_COUNT > 0){
      focusPose(f);
    	
      //
      
    }
    else printf("No Poses in the work list!\n");
  }
  else{printf("no skeleton!a\n");}
}

// Pose Timeline Functions
void asfApp::freshIndices(){
  int i=0;
  for (pose p : workPoses){
    p.index = i;
    i++;
  }
}

void asfApp::freshIntegrations(){
 for (auto x: boneCurveMap){
  x.second.measure(100); 
  x.second.integrate(); 
 } 
}

void asfApp::rawTimings(){
 for (auto x: boneCurveMap){
   int t = 0;
   x.second.timings.clear();
  for (pose p : workPoses) {
    x.second.timings.push_back(t);
    t++;
  }
 }
}

void asfApp::evenTimings(){
 freshIntegrations();
 for (auto x: boneCurveMap){
   float segCount = x.second.integration.size() - 1;
   float end = x.second.integration[segCount];
   rawTimings();
   float last = x.second.timings.size()-1;
   if (last > 0){
     for (float c :  x.second.timings) {
   float want = last * c/segCount;
   float thisT = x.second.bSearchForT(want);
   c = thisT;
   }
  }
 }
}

//Skeleton Initialisation

void asfApp::loadSkeleton(){

  nfdchar_t * skelFile;

  NFD_OpenDialog( "*", "", &skelFile);
  printf("\nloading %s\n",skelFile);
  loadSkeleton(skelFile);
}

void asfApp::loadSkeleton(const char * skelFile){
  showskel = new Skeleton(skelFile); //hmmmm.. malloc perhaps?
  //     showskel->setProgram(m_program);
  showskel->m_bonemesh = &m_mesh;
  showskel->m_jointmesh = &m_jointMesh;

  skelload = true;
  newWorkPose();

}

// TODO: put this in a lib or something. git it outa here!
// Helper method for retreiving and trimming the next line in a file.
// You should not need to modify this method.
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


void asfApp::play(){
  m_play = true;
}
void asfApp::pause(){
  m_play = false;
}

void asfApp::init(const char * skelFile) {

  if (skelFile) loadSkeleton(skelFile);
  else loadSkeleton();

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

cgra::Mesh asfApp::loadObj(char *filename) {

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
    m_play_pos += m_speed * 0.0004; showskel-> applyFromClip( theClip, m_play_pos);
    m_play_pos = glm::fract( m_play_pos );
  }
  stylePack = *(showskel->renderSkeleton( & m_mesh , tether));
}

float workRot[] = {0,0,0};


void asfApp::doGUI() {
  //the bonemap definitely works.
  ImGui::SetNextWindowSize(ImVec2(300, 50), ImGuiSetCond_FirstUseEver);
  ImGui::Begin(string("Joint Controls : ").append(currentJoint).c_str());

  //bone * boneptr = showskel->bonemap[currentJoint];//the bonemap works for bones above id 15.
  bone * boneptr = &(showskel->m_bones[showskel->findBone(currentJoint)]);


  if (boneptr){
    if (ImGui::SliderFloat3("Bone Rotation", &boneptr->rotation[0], -180 , 180 , "%.3f", 1.0f )){
    printf("moving bone %d\n", boneptr->boneID);
    //TODO:: update the entries in the curves?
  }
    if (ImGui::Button("Apply Quat")){
//      printf("bang!\n");
      quat asq = boneptr->getQuat();
      stringstream msg;
      msg << "rpy vector as quat:"<<asq.x<<" "<<asq.y<<" "<<asq.z<<" "<<asq.w<< "\n";
      printf("%s",msg.str().c_str());

      boneptr->applyQuat(asq);

    } 
  
  }

  ImGui::End();

  // --- Clip Controls
  ImGui::SetNextWindowSize(ImVec2(500, 50), ImGuiSetCond_FirstUseEver);
  ImGui::Begin("Shapes");
  
  if(ImGui::SliderFloat("Position", &m_play_pos, 0.f, 1.f, "%.5f", 1.0f)){
    showskel->applyFromClip(theClip,m_play_pos);
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

  ImGui::End();
}


// Input Handlers

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

//Joint editing funcs
//
void asfApp::focusBone(int i){
  if (showskel){
    if ( i > showskel->m_bones.size()-1){
      printf("Dont have a bone with that ID \n");
    }
    else{
      currentJointID  = i;
      currentJoint = showskel->m_bones[i].name;
      printf("focused %s \n", currentJoint.c_str());
    }

  }
}


void asfApp::poseToBones(pose & somePose){
  printf("asfAp poseToBones to be tested\n");

  boneCurveMap.clear();
  for (const auto x : somePose.my_frame){
    // Passing the whole map being iterated into the thing it maps to. This is either messy, or convenient?
    map<string,boneCurve>::iterator bc = boneCurveMap.find(x.first);
    if (bc != boneCurveMap.end())
      boneCurveMap[bc->first].newKF(&x.second); 

  }
}

int asfApp::getFrame(frame * dest){

  frame saveFrame;
  if (skelload == true) {
    saveFrame = showskel->makeFrame();
    *dest  = saveFrame;
  } else {  
    cout << (" No skeleton is posing!");
    return -1;
  }
  return 0;
}

void asfApp::focusPose(int f){
  focusIndex = f;
  if ( f > workPoses.size() ) return;
  currentWorkPose = &(workPoses[f]);
  showskel -> applyPose( &(workPoses[f].my_frame) );

}


void asfApp::newWorkPose(){
  pose newpose;
  int att = getFrame(   &newpose.my_frame   );
  newpose.index = workPoses.size();
  if (att>-1) workPoses.push_back(newpose);
  currentWorkPose = &(workPoses[workPoses.size()-1]);
  focusIndex = workPoses.size()-1;
}

void asfApp::setWorkPose(frame newframe){
  currentWorkPose->my_frame = newframe;
}



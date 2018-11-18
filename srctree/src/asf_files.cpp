#include "../include/nfd.h"

#include "includes-l1.hpp"

#include "asf.hpp"
#include "skeleton.hpp"
#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>
#include <istream>

using namespace std;
using namespace glm;

//These funcs return poses without indices, read from raw frame files.
//
//

#include <filesystem>


void asfApp::saveWorkPose(){
    nfdchar_t * toFile;
    NFD_SaveDialog(".pos","",&toFile);
    workPoseToFile(toFile);
  }


void asfApp::workPoseToFile(const char * filename){

  currentWorkPose -> filename = string(filename);

  //workPoses[focusIndex].my_frame = showskel -> makeFrame();
  ofstream pfs(filename);

  if (!pfs.is_open()) { printf("Cant open %s for writing!", filename); return; }

  //pfs << currentWorkPose->index << "\n";
  for ( const auto x : currentWorkPose->my_frame ){
    pfs << x.first << " ";
    for (float f : x.second) pfs << f << " ";
    pfs << "\n";
  }
  pfs.close();




}
void asfApp::openPose(){

  nfdchar_t * fromFile;
  NFD_OpenDialog(".pos,*",".",&fromFile); 
  const char * f = fromFile;
  openPose(f);
}

void asfApp::openPose(string file){
  const char * f = file.c_str();
  openPose(f);
}

void asfApp::openPose(  const char * fromFile ){


  newWorkPose();
  currentWorkPose = &(workPoses[workPoses.size()-1]);
  pose newp = poseFromFile( fromFile );
  (*currentWorkPose) = newp;
  currentWorkPose->index = workPoses.size()-1;
  showskel->applyPose(&(currentWorkPose->my_frame));
}

pose asfApp::poseFromFile( const char * fromFile){

  pose toPose;
  toPose.filename = string( fromFile );
  frame pf; pf.clear();

  ifstream pfilestream(fromFile);
  //   TODO: copy the right bits from the amc loader into here 
  //
  ifstream poseStream(fromFile);
  if (!poseStream.is_open()) {
    printf("Cant open pose!\n");
  } else{


    while (poseStream.good()){
      string line = nextLineTrimmed(poseStream); //get next line

      if (line.empty()|| line[0] == '#') //Comment Condition
        continue;
      else if (isdigit(line[0]))// Pose Index Condition 
      ; // { toPose.index = atoi(&line[0]); }
      else {
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
        pf[ thebone ] = rots; //copy the vector to the frame
      }
    }

    //breakpoint here
    printf("finished reading frame:");

  }

  toPose.my_frame = pf;

  return toPose;

}

//Assignemnt 2
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

  m_amc_play=true;
}

void asfApp::openSequenceFile(){

  nfdchar_t * fromFile;
  NFD_OpenDialog(".pos,*",".",&fromFile); 
  loadProjectFile(fromFile);
}

void asfApp::saveSequenceFile(){

  nfdchar_t * toFile;
  NFD_SaveDialog(".pos,*",".",&toFile); 
  projectToFile(toFile);

}

void asfApp::projectToFile(const char * filename){

  ofstream projFile(filename);

  for(int i = 0; i<workPoses.size(); i++){
    pose  * p = &(workPoses[i]);
   currentWorkPose = p;

  if (p->filename == "Unsaved"){ //Save the anon frames
    saveWorkPose();
  }
   projFile << p->filename << "\n";  
  }

  projFile.close();
}

void asfApp::loadProjectFile(const char * filename){

  ifstream projFile(filename);
  while(projFile.good()){
    string path;
    getline(projFile,path);
    if (path.length() > 1) openPose(path);  
  }
  projFile.close();
  
}

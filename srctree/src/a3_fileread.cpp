#include "../include/nfd.h"

#includes "includes-l1.hpp"

#include "a3.hpp"

using namespace stf;
using namespace glm;

//These funcs return poses without indices, read from raw frame files.
pose * a3_Application::openPose(){

  nfdchar_t * fromFile;
  NFD_SaveDialog(".pose,*",".",&fromFile); 

  return a3_poseFromFile( fromFile )
}
void a3_Application::a3_poseFromFile( char * fromFile, pose * toPose){

  ifstream pfilestream(fromFile);
//   TODO: copy the right bits from the amc loader into here 
//
    ifstream amcStream(aniFile);
    if (!amcStream.is_open()) {
    	printf("Cant open amc!\n");
    } else{
    
   frame pf; pf.clear();

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
		pf[ thebone ] = rots; //copy the vector to the frame
	//breakpoint here
	printf("finished reading frame:");

	}

  toPose->frame=pf;


    }


}



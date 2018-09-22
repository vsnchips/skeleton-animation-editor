#include "../include/nfd.h"

#include "a3.hpp"

using namespace std;
using namespace glm;

void a3_Application::a3_poseToFile( frame &somePose){

  nfdchar_t * toFile;
  NFD_SaveDialog(".pose,*",".",&toFile);

  ofstream pfilestream(toFile);


  if (!pfilestream.is_open()) printf("cant open %s for saving\n", toFile);
  else{
     printf("Saving this pose to %s\n", toFile);

     for (auto const x : somePose){
       pfilestream << x.first << " ";
       cout        << x.first << " ";
       for (float f : x.second){
         pfilestream << f << " ";
         cout        << f << " ";
       }
       pfilestream << '\n';
       cout << '\n';
       pfilestream.close();
     }

   }



}

void a3_Application::a3_writeAMC(){}

void a3_Application::a3_saveKeyFrames(){}

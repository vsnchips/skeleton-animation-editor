#pragma once

#include "splineMath.hpp"

using namespace glm;
using namespace std;

typedef std::vector<glm::quat> quatSpline;

glm::quat qSpline( float t, quatSpline & spline){
  //iterative decasteljau

  quatSpline temp = spline;
  int i = temp.size()-1;
  while( i>0){
    for (int j = 0; j < i; j++){
        temp[j] = slerp( temp[j], temp[j+1], t); 
      } i--;
  }
return temp[0];
}

vec2 splineSamp2D( float t, vector<vec2> spline){

  vector<vec2> temp = spline;
  int i = temp.size()-1;
while (i>0){
  for (int j=0; j<i; j++){
    temp[j] = mix( temp[j] , temp[j+1], t);
  }  i--;
}

return temp[0];


}

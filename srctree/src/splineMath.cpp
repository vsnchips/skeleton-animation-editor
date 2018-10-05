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

  vector<vec2> tempSpline(spline);
  int i = tempSpline.size()-1;
  while (i>0){
    for (int j=0; j<i; j++){
      tempSpline[j] = mix( tempSpline[j] , tempSpline[j+1], t);
    }  i--;
  }

  return vec2(tempSpline[0]);

}


vec2 catSamp2D ( float t, vector<vec2> & cats){
  return catSamp2D (t, cats, 0.25);
}

vec2 catSamp2D ( float t, vector<vec2> & cats, float bend){
  vec2 p = vec2(0);

  vector<vec2> spline; spline.clear();

  if (cats.size()<1) return p;
  else if(cats.size()<3) return cats[0];
  else if(cats.size()<4) return cats[1];
  else{
    vec2 a,ta,tb,b;

    float seg;
    t = modf(t, &seg);
    seg = glm::min(float(seg), float (cats.size()-4));
    seg = glm::max( seg, 0.f);
    
      //point A
      spline.push_back(
          cats[seg+1] 
          );
      //tan A
      spline.push_back( 
          cats[seg+1] + bend*(cats[seg+2] - cats[seg])
          );
      //tan B
      spline.push_back( 
          cats[seg+2] + bend*(cats[seg+1] - cats[seg+3])
          );
      //point b 
      spline.push_back( cats[seg+2] );
  }

  return splineSamp2D(t, spline);

}

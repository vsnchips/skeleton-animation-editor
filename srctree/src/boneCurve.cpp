#include "boneCurve.hpp"

using namespace std;
using namespace glm;

glm::quat testSpline( float t, quatSpline & spline){
  //iterative decasteljau

  int i = spline.size()-1;
  while( i>0){
    for (int j = 0; j < i; j++){
        spline[j] = slerp( spline[j], spline[j+1], t); 
      }
  } i--;
return spline[0];
} 


void boneCurve::setSamps(int i){
  samples = i;
}

void boneCurve::measure(int i){
  setSamps(i);
  measure();
}


quat getQuatBetween( quat p, quat q){
  return (q * glm::conjugate(p));
}

vector<quat> boneCurve::qBezFromCats( quat ca, quat a, quat b, quat cb){
  
  quat seg = getQuatBetween(a,b);
    float l = seg.x;

  quat ta = getQuatBetween(ca, b);
  ta.x = l/2;
  ta = ta*a;

  quat tb = getQuatBetween(cb, a);
  tb.x = l/2;
  tb = tb*b;

  vector<quat> q4bez; q4bez.clear();
  q4bez.push_back(a);
  q4bez.push_back(ta);
  q4bez.push_back(tb);
  q4bez.push_back(b);

  return q4bez;
}

void boneCurve::measure(){

  dds.clear();
  for (int j =1; j <= qcats.size()-3; j++){
    
    float sd = 1/(samples+1);

    vector<quat> qb;
    qb = qBezFromCats( qcats[j-1], qcats[j], qcats[j+1], qcats[j+2] );

    for (float t = 0 ; t < 1; t+=sd){
      dds.push_back(
          getQuatBetween(
            testSpline(t,qb), testSpline(t+sd,qb)
            ). x);
    }
  }
} 

void boneCurve::integrate(int i){
  setSamps(i);
  integrate();
}

void boneCurve::integrate(){
  integration.clear();
  float accd=0;
  integration.push_back(accd); //the fencepost
  for (int i = 0; i < dds.size(); i++){
    accd += dds[i];
    integration.push_back(accd);
  }
} 

quat boneCurve::getQuat( float t){

  // t should always be < qcats.size-3;
  // the floor call means you can never reach the end.
    int s = floor( t );
    float segt = s+fract(t);

    if (s >= qcats.size()-3){ segt=1; s= qcats.size()-3;}

    vector<quat> qs=qBezFromCats(qcats[s], qcats[s+1], qcats[+2], qcats[s+3]);
    //return testSpline( segt, qs[0], qs[1], qs[2], qs[3]);
    return testSpline( segt, qs);

}

float boneCurve::bSearchForT(float want){

  //bsearch which function?
  // 
  int l = 0; int h = integration.size()-1;
  float tl = integration[l];
  float th = integration[h];

  if (want < tl || want > th) return -1;

  while(h-l>0){
    int m=l + (h-l)/2;
    if (integration[m] > want) l++;
    else h--;
  }

  float a = integration[l];
  float b = integration[h];
  float t = (b-a)/(want-a);

  return (1-t)*l + t*h;

} 

void boneCurve::glDelete(){    //GL DELETE
    if (vbo != 0) {
            glDeleteBuffers(1, &vbo);
            vbo = 0;
        }
        if (ibo != 0) {
            glDeleteBuffers(1, &ibo);
            ibo = 0;
        }
        if (vao != 0) {
            glDeleteVertexArrays(1, &vao);
            vao = 0;
        }

        curveLineParticles.clear();
}

void boneCurve::updateCurveLineParticles(){
 curveLineParticles.clear();
 int sz = integration.size()-1;
 for ( int j = 0 ; j < timings.size()-2; j ++ ) {

  vector<vec2> thisSpline; thisSpline.clear();
  vec2 ca, a, b, cb;
  a  = (vec2(timings[j-0], integration[j-0]));
  b  = (vec2(timings[j+1], integration[j+1]));
  ca = (j > 0) ? 
    (vec2(timings[glm::max(j-1,0)], integration[glm::max(j-1,0)]))
    :
    a;
  cb = (j < timings.size()-3 )? 
    (vec2(timings[glm::min(j+2,sz)], integration[glm::min(j+2,sz)]))
    :
    b;
  
  float l = length(b-a)*0.5;
  ca = normalize(b-ca)*l;
  cb = normalize(cb-a)*l;
  thisSpline.push_back(a);
  thisSpline.push_back(ca);
  thisSpline.push_back(cb);
  thisSpline.push_back(b);

  for (int i = 0 ; i < samples; i++){ // Fill in the segment
    curveLineParticles.push_back(
        splineSamp2D( float(i)/float(samples), thisSpline )
        ); 
  }
 }

  glBindBuffer(GL_ARRAY_BUFFER,vao);
  size_t size = sizeof(vec2) * curveLineParticles.size();
  const void * ab = reinterpret_cast<const void *>(&curveLineParticles[0]);
  glBufferData(GL_ARRAY_BUFFER, size, ab,GL_DYNAMIC_DRAW);
}


void boneCurve::freshBuffs(){  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao) ;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(vec2),0);
  glEnableVertexAttribArray(0);
 
}

// Draw Style method!
vector<drawStyle> boneCurve::getStyle(){
  vector<drawStyle> cstyle; cstyle.clear();
  vector<mat4> ts; ts. clear();

  //GL Buffers
  if (vbo == 0 || ibo == 0 || vao == 0) { //Refresh buffers!
  glDelete();
  freshBuffs();

    }

  drawStyle lStyle;
  lStyle.mode = GL_LINE_STRIP;
  GLuint pbuff;
  glGenBuffers(1,&pbuff);
//  gl
  for(int i = 1; i<catreps.size()-1; i++){ //includes dummies
     
  
  }

  return cstyle;

}

void boneCurve::movePoint( int id, glm::vec2 dv){
      catreps[id].x += dv.x;
}


void boneCurve::newKF (pose & newpose){
 //convert the euler angle to a quaternion  
	const float DEGMUL = pi<float>()/180;
  

}

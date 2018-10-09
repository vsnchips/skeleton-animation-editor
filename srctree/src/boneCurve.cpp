#include "boneCurve.hpp"

using namespace std;
using namespace glm;

glm::quat testSpline( float t, quatSpline & spline){
  //iterative decasteljau

  int i = spline.size()-1;
  while( i>0){
    for (int j = 0; j < i; j++){
        spline[j] = slerp( spline[j], spline[j+1], t); 
      } i--;
  } 
return spline[0];
} 


void boneCurve::setSamps(int i){
  samples = i;
}

dquat getQuatBetween_Double( dquat p, dquat q){
  return (q * glm::conjugate(p));
}
quat getQuatBetween( quat p, quat q){
  return (q * glm::conjugate(p));
}

quat boneCurve::getSplineQuat( float t){      //The raw t value.

  // t should always be < qcats.size-3;
  // the floor call means you can never reach the end.
    int s = floor( t );
    float segt = fract(t);

    if (s >= qcats.size()-3){ segt=1; s = qcats.size()-3;}

    vector<quat> qs=qBezFromCats(qcats[s], qcats[s+1], qcats[s+2], qcats[s+3]);
    return testSpline( segt, qs);

}

vector<quat> boneCurve::qBezFromCats( quat ca, quat a, quat b, quat cb){
  
  quat seg = getQuatBetween(a,b);
  vec3 segVec = vec3(seg.x,seg.y,seg.z);
  float l = atan2( length(segVec), seg.w);

#define CATROM_CURVE_COEFF 0.5f
  quat ta = getQuatBetween(ca, b);
  //ta = ta*a*conjugate(ta);
  ta = conjugate(ta)*a*ta;
  ta = slerp(a,ta,l*CATROM_CURVE_COEFF);

  quat tb = getQuatBetween(cb, a);
  // tb = tb*b*conjugate(tb);
  tb = conjugate(tb)*b*tb;
  tb = slerp(b,tb,l*CATROM_CURVE_COEFF);

  vector<quat> q4bez; q4bez.clear();
  q4bez.push_back(a);
  q4bez.push_back(ta);
  q4bez.push_back(tb);
  q4bez.push_back(b);

  return q4bez;
}

void boneCurve::measure(int i){
  setSamps(i);
  measure();
}

void boneCurve::measure(){

  dds.clear();
  for (int j = 0; j < qcats.size()-3; j++){
    
    float sd = 1.f/float(samples+1);

    vector<quat> qb;
    qb = qBezFromCats( qcats[j], qcats[j+1], qcats[j+2], qcats[j+3] );
    for (float t = 0 ; t < 1; t+=sd){
    
      dquat dq = getQuatBetween_Double(
            dquat(testSpline(t,qb)), 
            dquat(testSpline(t+sd,qb))
            );
      vec3 segVec = vec3(dq.x,dq.y,dq.z);
      float d = abs(2.f*atan2(length(segVec), dq.w));
      if (d>0.1) printf(" dQ magnitude: %5f \n", d);
      dds.push_back(d);
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

quat boneCurve::getQuatAtDistance(float dist){
  if ((dds.size() == 0)) 
  {
    //printf("Unintegrated BoneCurve \n");
    measure(); 
    integrate();
    printf("Integrated BoneCurve: %d Samples\n", dds.size());
  }

//  float ndist = dist/(qcats.size()-3);
  float t = bSearchForT( dist );
  return getSplineQuat(t);
}

float boneCurve::bSearchForT(float want_relative){

  //bsearch which function?
  // 
  int l = 0; int h = integration.size()-1;
  float tl = integration[l];
  float th = integration[h];

  //map tl:th to 0:segments
  int segs = qcats.size()-3;
  float want = th*want_relative/segs; // want to get a distance along the path

  //if (want < 0 || want > th) return -1;

  while((h-l)>1){
    int m = l + (h-l)/2;
    if (integration[m] > want) h = m;
    else l = m;
  }

  //want is between a and b
  float a = integration[l];
  float b = integration[h];
  if (b-a == 0){
    cout << "zero integral" << "\n";
    return 0 ;   // bandage
  }
  float t = (want-a)/(b-a);
  //Interpolate the integration function indices
  float t_integrationScale = (1.f-t)*float(l) + t*float(h);

  float t_segScale = segs * t_integrationScale / (integration.size()-1);
  return t_segScale; 

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


void boneCurve::freshBuffs(){
  
  glGenVertexArrays(1, &vao);
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
  lStyle.tag = "lines";
  lStyle.unfms.m4["modelMat"] = mat4(1);
  lStyle.primCount = 50;
  
//(catreps.size()-3)*10;
//  gl
//
  std::vector<vec2> pbuff; pbuff.clear();
  for(int i = 0; i<catreps.size()-3; i++){ //includes dummies
    for ( int j = 0; j < 10; j++){
            float t = i+float(j)/11.f;
      pbuff.push_back( catSamp2D(  t , catreps ));
    }
  }

  glBindVertexArray(vao) ;
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * pbuff.size(), &pbuff[0], GL_DYNAMIC_DRAW );

  lStyle.vao = vao;
  cstyle.push_back(lStyle);
  return cstyle;

}

void boneCurve::movePoint( int id, glm::vec2 dv){
      catreps[id].x += dv.x;
}


void boneCurve::newKF(const vector<float> * xyz){
 //convert the euler angle to a quaternion  
	const float DEGMUL = pi<float>()/180;
  mat4 r = rotate(mat4(1), (*xyz) [0], vec3(1,0,0));;
       r = rotate(mat4(1), (*xyz) [1], vec3(0,1,0)) * r;
       r = rotate(mat4(1), (*xyz) [2], vec3(0,0,1)) * r;


  

}

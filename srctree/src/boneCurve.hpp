#pragma once  
#include "includes-l1.hpp" 
#include "splineMath.hpp"
#include "drawStyle.hpp"
#include "skeleton.hpp"
//#include ""

class boneCurve{
  public:

    std::vector<drawStyle> getStyle();
    
    //gl stuff
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ibo = 0;

    void updateCurveLineParticles();
    std::vector<glm::vec2>curveLineParticles;
          
    void glDelete();    //GL DELETE
    void freshBuffs();

#define DEFAULT_SAMPLES 20
    int samples = DEFAULT_SAMPLES;
    std::vector<glm::vec3> cats;  //always includes dummies
    std::vector<glm::quat> qcats;  //always includes dummies
    std::vector<glm::vec2> catreps;
    std::vector<float> timings;  // the first pose is always at 0, but every kf has a time. 

    std::vector<float> dds; // one for every path segment
    std::vector<float> integration;  //one for every kf.

    std::vector<glm::quat> qBezFromCats( glm::quat ca, glm::quat a, glm::quat b, glm::quat cb);

    void measure(int );
    void integrate(int ); //includes a measure method
    void measure();
    void integrate(); //includes a measure method
    float bSearchForT(float wantdist);
    glm::quat getQuatAtDistance(float); 
    glm::quat getSplineQuat(float chrono);

    void setSamps(int s);
    void movePoint( int id, glm::vec2 dv);

    void newKF( const std::vector<float> * );
    
};

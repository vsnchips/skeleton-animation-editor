#pragma once

#include "includes-l1.hpp"

typedef std::vector<glm::quat> quatSpline;

glm::mat4 rotMatFromQuatSpline(quatSpline s,float t);

class a3Curve{

  public:

    quatSpline m_quatspline;
    int segments;
    int sampcount;

  void calcTable();




};
float t_at_time

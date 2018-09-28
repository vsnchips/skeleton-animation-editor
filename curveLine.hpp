#pragma once

#include "includes.hpp"
#include "splineMath.hpp"

class curveLine{

  public:
    std::vector<glm::vec3> points;
    std::vector<drawStyle> drawLineStyle();

};

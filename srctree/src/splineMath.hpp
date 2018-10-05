#pragma once

//#include "includes-l1.hpp"

#include <vector>

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"


typedef std::vector<glm::quat> quatSpline;

glm::mat4 rotMatFromQuatSpline(quatSpline s,float t);

glm::vec2 splineSamp2D( float t, std::vector<glm::vec2> spline);
glm::quat qSpline( float t, std::vector<glm::quat> spline);

glm::vec2 catSamp2D(float, std::vector<glm::vec2> &);

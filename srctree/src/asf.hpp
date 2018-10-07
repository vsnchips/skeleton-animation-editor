#pragma once

#include <algorithm>
#include <cmath>
#include <istream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>

#include "opengl.hpp"
#include "imgui.h"

#include "math.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include <vector>
#include <map>
#include <fstream>

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"
#include "cgra/mesh.hpp"
#include "cgra/shader.hpp"
#include "drawStyle.hpp"

#include "../include/nfd.h"

#include <skeleton.hpp>
#include "boneCurve.hpp"

class asfApp {

  public:
    
    //General State
    bool skelload =  false;

     // actors in the play:
    Skeleton * showskel;
    cgra::Mesh m_mesh;
    cgra::Mesh m_jointMesh;

    //example poses
    frame sittingPose;
    frame guitarPose;
    frame walkingPose;
    frame currentFrame;
    
    //Pose Management
    std::vector<pose> workPoses;
    pose * currentWorkPose;
    void setWorkPose(frame);
    void focusPose(int);
    void newWorkPose();

    void openPose();
    pose poseFromFile( char *); // Reads a pose file into a constructed pose.
    void poseToFile( char *, pose *);   // Saves a given pose to a file
    void workPoseToFile( char *);
   
    //Animation:
    void poseToBones( pose & somePose);
    int getFrame(frame * dest);
    std::map<std::string,boneCurve> boneCurveMap;
    
    //Demo Poses
    void prevPose();
    void nextPose();
    void switchPose(int dir);

    //Editing Functionality
    void focusBone( int i );
    std::string currentJoint = "root";
    int currentJointID;

    void loadSkeleton(const char *);
    void loadSkeleton();
    
    //AMC Player:
    void loadAnimation();
    void play();
    void pause();

    bool m_play = false;
    float m_play_pos;
    bool tether = true;
    float m_speed;
    std::vector<frame> theClip;


// glm view stuff:
    glm::vec2 m_viewportSize;
    glm::vec2 m_mousePosition;
    glm::vec2 m_kfMousePos;
    glm::vec3 m_translation;
    float m_scale;

    // A 4x4 matrix representing the rotation of the
    // mesh,
    // And a vec3 with the z/y/x/ coords.

    glm::vec3 xax,yax,zax;
    glm::vec3 polarrotation;
    glm::mat4 m_rotationMatrix;

    // Whether or not the left, middle or right buttons are down.
    bool m_mouseButtonDown[3];


    //admin:
    GLFWwindow *m_window;

    cgra::Program m_program;
     //
     //
    asfApp(GLFWwindow *win)
        : m_window(win),
          m_viewportSize(1, 1), m_mousePosition(0, 0),
          m_translation(0), m_scale(1), m_rotationMatrix(1) {
        m_mouseButtonDown[0] = false;
        m_mouseButtonDown[1] = false;
        m_mouseButtonDown[2] = false;
    }


//admin
    void setWindowSize(int width, int height) {
        m_viewportSize.x = float(width);
        m_viewportSize.y = float(height);
    }

    void init(const char *);

    void createCube();
    cgra::Mesh loadObj( char *filename);

    std::vector<drawStyle> stylePack;
    void updateScene();
    void calcJointsFromXYZ();
    

//Events
    
    void doGUI();
    void onKey(int key, int scancode, int action, int mods);
    void onMouseButton(int button, int action, int mods);
    void onCursorPos(double xpos, double ypos);
    void onScroll(double xoffset, double yoffset);

};


std::string nextLineTrimmed(std::istream &file);

#pragma once

#include "cgra/mesh.hpp"
#include "cgra/shader.hpp"

#include <glm/glm.hpp>

#include <skeleton.hpp>

class Application {
public:

    void loadSkeleton();

// actors in the play:	
    Skeleton * showskel;
   cgra::Mesh m_mesh;

// glm view stuff:
    glm::vec2 m_viewportSize;
    glm::vec2 m_mousePosition;
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
    Application(GLFWwindow *win)
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

    void init();

    void createCube();
    void loadObj(const char *filename);

    void drawScene();
    void doGUI();

    void onKey(int key, int scancode, int action, int mods);

    void onMouseButton(int button, int action, int mods);

    void onCursorPos(double xpos, double ypos);

    void onScroll(double xoffset, double yoffset);
};

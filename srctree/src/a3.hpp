#pragma once

#include "cgra/mesh.hpp"
#include "cgra/shader.hpp"

#include "glm/glm.hpp"
#include "asf.hpp"
#include "app_renderer.hpp"

typedef struct shareGlobals{
//fill this later

}myGlobs;

class a3_Application {
public:
    bool clickon;
    int deformTechniqueId;
    bool sceneon = 1;
    int pickID;
    int pickNode;
    int lx = 2,ly = 2,lz = 2;
    float pickDepth=1;
    GLint triangleMode;

    asfApp * theAsfApp;
    app_renderer a3Renderer;
    /////////////////////////////////////////// Part 1 Vars
    // The window object managed by GLFW
    GLFWwindow *m_window;
    // The shader program used for drawing
    cgra::Program m_program;
    // The mesh data
    cgra::Mesh m_mesh;
    cgra::Mesh m_spheremesh;

    // The current size of the viewport
    glm::vec2 m_viewportSize;
    // The current mouse position
    glm::vec2 m_mousePosition;

    // The translation of the mesh as a vec3
    glm::vec3 m_translation;
    // The scale of the mesh
    float m_scale;

    // A 4x4 matrix representing the rotation of the
    // mesh,
    // And a vec3 with the z/y/x/ coords.

    glm::vec3 xax,yax,zax;
    glm::vec3 polarrotation;
    glm::mat4 m_rotationMatrix,m_modelTransform;

    // Whether or not the left, middle or right buttons are down.
    bool m_mouseButtonDown[3];

    a3_Application(GLFWwindow *win)
        : m_window(win),
          m_viewportSize(1, 1), m_mousePosition(0, 0),
          m_translation(0), m_scale(1), m_rotationMatrix(1) {
        m_mouseButtonDown[0] = false;
        m_mouseButtonDown[1] = false;
        m_mouseButtonDown[2] = false;
    }

    void setWindowSize(int width, int height) {
        m_viewportSize.x = float(width);
        m_viewportSize.y = float(height);
    }

    void init();
    void reloadShader();

    void createCube();
    void loadObj(const char *filename,cgra::Mesh &);

    void drawScene();
    void doGUI();

    void onKey(int key, int scancode, int action, int mods);

    void onMouseButton(int button, int action, int mods);

    void onCursorPos(double xpos, double ypos);

    void onScroll(double xoffset, double yoffset);

    int pickTest(float mX, float mY);
    int pickTest();

    //File saving methods

    void a3_poseToFile(frame & somePose);

    void a3_writeAMC();

    void a3_saveKeyFrames();
};

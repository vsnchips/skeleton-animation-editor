#pragma once

#include "opengl.hpp"

// Forward definition of callbacks
extern "C" {
     void glfw_error_callback(int error, const char* msg);

    void APIENTRY debugCallback(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*, GLvoid*);

     void key_callback(GLFWwindow *, int, int, int, int);
     void mouse_button_callback(GLFWwindow *, int, int, int);
     void cursor_pos_callback(GLFWwindow *, double, double);
     void scroll_callback(GLFWwindow *, double, double);
     void char_callback(GLFWwindow *, unsigned int codepoint);
}



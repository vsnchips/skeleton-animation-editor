#include <stdio.h>

#include <iostream>
#include <iomanip>

#include "opengl.hpp"

#include "imgui.h"
#include "cgra/imgui_impl_glfw_gl3.h"

#include "a3.hpp"
#include "callbacks.hpp"

#include <chrono>
#include <thread>

using namespace std::literals;

int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: Could not initialize GLFW" << std::endl;
        return 1;
    }
    glfwSetErrorCallback(glfw_error_callback);
  // Read the OpenGL version
    GLint glMajor, glMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glMinor);

    // // Read the GLFW version
    int glfwMajor, glfwMinor, glfwRevision;
    glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "GLFW Version: " << glfwMajor << '.' << glfwMinor << '.' << glfwRevision << std::endl;

    /*// Enable debug messages if available
    if (glMajor > 4 || (glMajor == 4 && glMinor >= 3)) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(debugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
    } else if (GLEW_ARB_debug_output) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);

        glDebugMessageCallbackARB(debugCallback, nullptr);
        glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
    }
*/

        {
        // Create the application object
        a3_Application app = a3_Application();
   /* 
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
  app.keyframe_window = glfwCreateWindow(1000,1000, "Curve Editor", NULL,window) ;
   glfwMakeContextCurrent(app.keyframe_window);

   // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Enable backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

*/   
     
     
     
     // Tell GLFW to pass along a pointer to `app` in callbacks

        try {
			// Initialise `app`
      const char * skelPath = nullptr;//"";
      if (argc > 1){skelPath = argv[1];}
      app.launch(skelPath);
     
    //TODO: copy this to editor_thread
    /*
      // Loop until the GLFW window is marked to be closed
            while (!glfwWindowShouldClose(app.m_window)) {
                // Poll GLFW for input events
                glfwPollEvents();                // Draw the scene.
                app.drawScene();
	std::this_thread::sleep_for(5ms);
            }

            */


        } catch (std::exception e) {
            // Catch any exceptions that bubble up to here and print out
            // the message
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    // Clean up
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    // 0 is the "everything went OK" value when returned from
    // main
    return 0;
}



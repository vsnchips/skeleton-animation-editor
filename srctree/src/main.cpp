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
<<<<<<< HEAD
        a3_Application app(window);
    
=======
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
     
     
     
>>>>>>> 9a577229aa718f179264d1981593f53a65ac11fb
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

<<<<<<< HEAD
static const char *getStringForSource(GLenum source) {

    switch(source) {
    case GL_DEBUG_SOURCE_API:
        return("API");
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return("Window System");
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return("Shader Compiler");
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return("Third Party");
    case GL_DEBUG_SOURCE_APPLICATION:
        return("a3_Application");
    case GL_DEBUG_SOURCE_OTHER:
        return("Other");
    default:
        return("n/a");
    }
}

static const char *getStringForSeverity(GLenum severity) {

    switch(severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        return("HIGH!");
    case GL_DEBUG_SEVERITY_MEDIUM:
        return("Medium");
    case GL_DEBUG_SEVERITY_LOW:
        return("Low");
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return("None");
    default:
        return("n/a");
    }
}

static const char *getStringForType(GLenum type) {
    switch(type) {
    case GL_DEBUG_TYPE_ERROR:
        return("Error");
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return("Deprecated Behaviour");
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return("Undefined Behaviour");
    case GL_DEBUG_TYPE_PORTABILITY:
        return("Portability Issue");
    case GL_DEBUG_TYPE_PERFORMANCE:
        return("Performance Issue");
    case GL_DEBUG_TYPE_OTHER:
        return("Other");
    default:
        return("n/a");
    }
}
extern "C" {
    static GLenum g_prevSource;
    static GLenum g_prevType;
    static GLenum g_prevSeverity;
    static GLenum g_prevId;
    static int g_headerCount = 0;

    void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, const GLchar* message, GLvoid*) {
        // Don't report notification messages
        if (severity == GL_DEBUG_SEVERITY_LOW ) return; // TODO: Defer these warnings to some less annoying output
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

        if (id == g_prevId) return;
        if (g_headerCount == 0 || g_prevSource != source || g_prevType != type || g_prevSeverity != severity) {
            std::cerr << std::endl; // extra space
            std::cerr << "Type: " <<
                getStringForType(type) << "; Source: " <<
                getStringForSource(source) <<"; Severity: " <<
                getStringForSeverity(severity) << std::endl;

            g_headerCount = 0;
        }

        // If more than 128 messages have come through without printing a new header,
        // this will cause one to be printed next time
        g_headerCount = (g_headerCount + 1) % 128;

        g_prevSource   = source;
        g_prevType     = type;
        g_prevSeverity = severity;
        g_prevId       = id;

        std::cerr << '[' << std::setw(3) << id << "] " << message << std::endl;
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;

        ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);

        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureKeyboard) return;

        app->onKey(key, scancode, action, mods);
    }

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;
=======
>>>>>>> 9a577229aa718f179264d1981593f53a65ac11fb


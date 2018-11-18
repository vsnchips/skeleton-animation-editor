#include "callbacks.hpp"
#include "imgui.h"
#include "cgra/imgui_impl_glfw_gl3.h"

#include <string>
#include <iostream>
#include <iomanip>

#include "a3.hpp"

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

     void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;

        ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);

        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureKeyboard) return;

        app->onKey(key, scancode, action, mods);
    }

     void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;

        ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);

        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureMouse) return;

        app->onMouseButton(button, action, mods);
    }

     void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;

        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureMouse) return;

        app->onCursorPos(xpos, ypos);
    }

     void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;

        ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);

        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureMouse) return;

        app->onScroll(xoffset, yoffset);
    }

     void char_callback(GLFWwindow *window, unsigned int codepoint) {
        a3_Application *app = (a3_Application *)glfwGetWindowUserPointer(window);
        if (app == nullptr) return;

        ImGui_ImplGlfwGL3_CharCallback(window, codepoint);
        ImGuiIO& io = ImGui::GetIO();
        if (io.WantTextInput) return;

        // Don't pass along char callback events for now
    }

     void glfw_error_callback(int error, const char* msg) {
        std::cerr << "GLFW Error (" << error << "): " << msg << std::endl;
    }
}

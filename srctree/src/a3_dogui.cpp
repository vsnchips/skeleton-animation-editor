#include "includes-l1.hpp"

#include "a3.hpp"

#include "imgui.h"
#include "skeleton.hpp"

#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

void a3_Application::doGUI() {

    theAsfApp->doGUI();

    ImGui::Begin("Working Pose Status");
    if (theAsfApp && theAsfApp -> skelload) ImGui::Text("Pose Keyframe index # %d:" , theAsfApp -> currentWorkPose->index );
    ImGui::End(); 

    ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");

    /************************************************************
     *                                                          *
     * 2. Load an .obj file                                     *
     *                                                          *
     * Add an input for a filename.                             *
     *                                                          *
     ************************************************************
     *                                                          *
     * 3. Manual Transforms                                     *
     *                                                          *
     * Create inputs for controlling translation, scale and     *
     * rotation.                                                *
     *
     ************************************************************
     */

    ImGui::SliderFloat3("Translate",&m_translation[0],-20.0f,20.0f, "%.5f",1.5f);
    ImGui::SliderFloat("Scale",&m_scale,0,5.0f, "%.5f", 2.5f);
    if(ImGui::SliderFloat3("Rotate",&polarrotation[0],-M_PI,M_PI, "%.5f", 1.0f)){
        // User's spun the globe
        // Find the resulting matrix!

        //1. Transform the Z/north pole, X/west, and Y/celestial vectors via the input lat/long TODO: How do i get this into a mat3x3?
     if ( polarrotation.x == 0 ){
         zax = glm::vec3(0,0,1);
         yax = glm::vec3(0,1,0);
         xax = glm::vec3(1,0,0);
     }
     else {
         //fix for negative latitudes:
         float polx,poly;
         if (polarrotation.x < 0){
             polx =-polarrotation.x;
             poly = polarrotation.y + M_PI;
         } else {
             polx = polarrotation.x;
             poly = polarrotation.y;
         }

         zax = glm::rotate(
                    (glm::rotate(glm::vec3(0.,0.,1.),polx,glm::vec3(0.,1.,0.))) // tilt it on Y over to X to latitude
                    ,poly, glm::vec3(0.,0.,1.));  // spin it on true Zorth to longtitude

        //2.Find the normal and angle between Zorth and the new Z, and apply the same rotation to Xwest and YCelestial
        glm::vec3 tnorm = glm::cross(glm::vec3(0.,0.,1.),zax);
        yax = glm::rotate(glm::vec3(0.,1.,0.),polx,tnorm);
        xax = glm::rotate(glm::vec3(1.,0.,0.),polx,tnorm);
      }
        //3. Rotate X and Y around the tilted Z pole/
        yax = glm::rotate(yax, polarrotation.z, zax);
        xax = glm::rotate(xax, polarrotation.z, zax);

    };

    ImGui::End();

    if (theAsfApp->skelload){
    ImGui::Begin("Keyframe Poses");
    ImGui::Checkbox("Toggle Keyframe Editor",&kf_window_see);
    for( int i= 0 ; i < theAsfApp -> workPoses.size(); i++)   {      //one radio button for each pose

      pose * p; p = & (theAsfApp -> workPoses[i]);
      stringstream button;
      button << p->index << " : " << fs::relative( p -> filename.c_str(), fs::current_path() ) << " " << (theAsfApp->currentWorkPose == p ? "<< current" : "");

      if(ImGui::RadioButton(button.str().c_str(),
            theAsfApp->focusIndex == i)) 
          {
          theAsfApp -> focusIndex = i; 
          theAsfApp -> focusPose(i);
          }
    } 
    ImGui::End();
    
    ImGui::Begin("Keyframe Operations");
     
    if(ImGui::Button("Push Pose As New Keyframe")) {
      theAsfApp -> newWorkPose();
    }
    if (ImGui::Button("next Pose")){ theAsfApp->nextPose();}
    if (ImGui::Button("prev Pose")){ theAsfApp->prevPose();}
    if (ImGui::Button("Remove Pose")){ theAsfApp->removePose();}
    ImGui::End();
    }

    ImGui::Begin("Shader Controls");
    if(ImGui::Button("Toggle Picker Test")){
<<<<<<< HEAD
      a3Renderer.previewPick = !a3Renderer.previewPick;
    //  a3_kf_renderer.previewPick = !a3_kf_renderer.previewPick;
=======
      a3Renderer->previewPick = !a3Renderer->previewPick;
>>>>>>> 9a577229aa718f179264d1981593f53a65ac11fb
    }

    if (ImGui::Button("Reload Shader")){ 
      a3Renderer->loadPickShader();
      cout<< "loaded Pickshader\n";
    }
    ImGui::End();

    ImGui::Begin("File Menu");
    if (ImGui::Button("Load a Keframe Sequence")){ theAsfApp -> openSequenceFile();}
    if (ImGui::Button("Save this Keyframe Sequence")){ theAsfApp -> saveSequenceFile();}
    if (ImGui::Button("Load an AMC")){ theAsfApp -> loadAnimation();}
    if(ImGui::Button("Load a Pose")) {
        theAsfApp -> openPose();
      }

    if(ImGui::Button("Save Pose (S Key)")){
      theAsfApp -> saveWorkPose();
    }
       ImGui::End();

    ImGui::Begin("meshes");
    static bool wireframe;
    if(ImGui::Checkbox("Draw Wireframe",&wireframe)) {
        m_mesh.setDrawWireframe(wireframe);
    }

    //debugging stuff:
    ImGui::Text("tricount :%d" , m_mesh.m_indices.size()/3);
    ImGui::Text("vertcount : %d" , m_mesh.m_vertices.size());

    ImGui::End();
}

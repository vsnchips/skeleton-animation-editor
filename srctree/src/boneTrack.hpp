#include "includes-l1.hpp"


class boneTrack{

  public:
    std::vector<Pose> * poseList;
   
    std::vector<float> timings;

    //pass in reference to snaps
    void snapPose(int index){
      timings.at(index ) = poseList->at(index).nomTime;
      
    }
}

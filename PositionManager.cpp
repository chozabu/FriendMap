#include "PositionManager.h"

PositionManager::PositionManager()
{

}

Offset::Offset(){
    distance = 0.3;
    angle = 0;
}

Offset::Offset(double angle, double distance){
    this->distance = distance;
    this->angle = angle;
}

Offset Offset::getIncreased(){
    double new_distance = distance;
    double new_angle = angle+angular_step;
    if(TAU - new_angle < 0.0001){
        new_distance += 0.3;
        new_angle = 0;
    }
    Offset increased(new_angle, new_distance);
    return increased;
}

#include "Neat.h"
#include <iostream>

CNeat::CNeat(){

}

CNeat::~CNeat(){

}

void CNeat::SetActionValues( double delta_x, double delta_y,
                             double delta_direction){

//    std::cout << "In Neat.cpp, SetActionValues." << std::endl;
    _delta_x = delta_x;
    _delta_y = delta_y;
    _delta_direction = delta_direction;
//    std::cout << "In Neat.cpp, _x: " << _x << ", _y: " << _y << std::endl;
}

CGeoPoint CNeat::GetPosition(const CVisionModule *pVision, const int num){
    _x = pVision->OurPlayer(num).X() + _delta_x;
    _y = pVision->OurPlayer(num).Y() + _delta_y;
//    std::cout << "In Neat.cpp, runner number: " << num
//              << ", _delta_x: " << _delta_x
//              << ", _delta_y: " << _delta_y << std::endl;
    _param_position.setX(_x);
    _param_position.setY(_y);
    return _param_position;
}

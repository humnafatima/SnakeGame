#pragma once
#include "Position.h"


enum class Direction { UP, DOWN, LEFT, RIGHT }; //a new data type 

class Brain {
public:
    Brain(); // constructor, will set the starting direction to RIGHT
    void setDirection(Direction newDir); //Take input from WASD 
     Direction getDirection() const;
     Position computeNextHead(const Position& head) const; //TAKES CURRENT HEAD POSITION AND RETURN NEXT HEAD POSITION 


     private:
    Direction current;
    bool isOpposite(Direction a, Direction b) const;
};

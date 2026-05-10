// simple struct but essential: every single file uses it (snake.h, food.h, obstacle.h, gamecontroller.cpp)
//without it we would have to pass x and y as two separate integers EVERYWHERE AHHH 
//position is a helper class, represents a coordinate on the grid

#pragma once

class Position {
public:
    int x;
    int y;

    Position(int x = 0, int y = 0);

    bool operator==(const Position& other) const; //operator overloading 
    bool operator!=(const Position& other) const;  
};
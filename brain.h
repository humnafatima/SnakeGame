#pragma once
#include "snake.h"  // gets us Position and Direction

class Brain {
public:
    Brain();

    void setDirection(Direction newDir);
    Direction getDirection() const;
    Position computeNextHead(const Position& head) const;

private:
    Direction current;
    bool isOpposite(Direction a, Direction b) const;
};
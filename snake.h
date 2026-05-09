#pragma once
#include "Position.h"
#include <list>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    std::list<Position> body;
    Direction dir;
    Direction nextDir;
    bool growing;

public:
    Snake();

    // Rule of Three
    Snake(const Snake& other);
    Snake& operator=(const Snake& other);

    // Operator overload
    bool operator==(const Snake& other) const;

    // What GameController calls
    void update();
    void draw();
    void grow();
    bool checkSelfCollision() const;
    Position getHead() const;

    // Extras
    void changeDirection(Direction newDir);
    bool containsPosition(const Position& p) const;
    std::list<Position>& getBody();
};
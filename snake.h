//humna 

#pragma once
#include <raylib.h> //needed for colour since its a raylib type
#include "Position.h"
#include <list>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    std::list<Position> body;
    Direction dir;
    Direction nextDir;
    bool growing;
    int upKey, downKey, leftKey, rightKey;  // customizable controls

public:
    Snake();
    Snake(int startX, int startY, int upKey, int downKey, int leftKey, int rightKey);

    const std::list<Position>& getBody() const;

    // Rule of Three
    Snake(const Snake& other);
    Snake& operator=(const Snake& other);
    bool operator==(const Snake& other) const;

    void update();
    void draw(Color headColor, Color bodyColor);  // each player different color
    void grow();
    bool checkSelfCollision() const;
    bool collidesWithOther(const Snake& other) const;  // 2 player collision
    Position getHead() const;
    void changeDirection(Direction newDir);
    bool containsPosition(const Position& p) const;
    std::list<Position>& getBody();
    int getLength() const { return (int)body.size(); }
};
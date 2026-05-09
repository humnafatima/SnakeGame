#pragma once
#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Position {
public:
    int x, y;
    Position(int x = 0, int y = 0);
    bool operator==(const Position& other) const;
};

class Snake {
private:
    std::vector<Position> body;
    Direction dir;

public:
    Snake();

    void move();
    void changeDirection(Direction newDir);

    std::vector<Position>& getBody();
};
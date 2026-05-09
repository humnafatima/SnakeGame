#include "snake.h"

// Position
Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

// Snake
Snake::Snake() {
    body.push_back(Position(10, 10));
    dir = RIGHT;
}

void Snake::move() {

    Position head = body[0];

    if (dir == UP) head.y--;
    else if (dir == DOWN) head.y++;
    else if (dir == LEFT) head.x--;
    else if (dir == RIGHT) head.x++;

    body.insert(body.begin(), head);
    body.pop_back(); // constant length snake (important for visibility)
}

void Snake::changeDirection(Direction newDir) {

    if ((dir == UP && newDir == DOWN) ||
        (dir == DOWN && newDir == UP) ||
        (dir == LEFT && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) {
        return;
    }

    dir = newDir;
}

std::vector<Position>& Snake::getBody() {
    return body;
}
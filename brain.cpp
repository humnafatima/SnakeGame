#include "brain.h"

Brain::Brain() : current(RIGHT) {}  // no Direction:: because it's a plain enum

void Brain::setDirection(Direction newDir) {
    if (!isOpposite(newDir, current))
        current = newDir;
}

Direction Brain::getDirection() const {
    return current;
}

Position Brain::computeNextHead(const Position& head) const {
    switch (current) {
        case UP:    return Position(head.x, head.y - 1);
        case DOWN:  return Position(head.x, head.y + 1);
        case LEFT:  return Position(head.x - 1, head.y);
        case RIGHT: return Position(head.x + 1, head.y);
    }
}

bool Brain::isOpposite(Direction a, Direction b) const {
    return (a == UP    && b == DOWN)  ||
           (a == DOWN  && b == UP)    ||
           (a == LEFT  && b == RIGHT) ||
           (a == RIGHT && b == LEFT);
}
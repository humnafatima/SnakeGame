#include "brain.h"

Brain::Brain() : current(Direction::RIGHT) {}

void Brain::setDirection(Direction newDir) {
    if (!isOpposite(newDir, current))
        current = newDir;
}

Direction Brain::getDirection() const {
    return current;
}

Position Brain::computeNextHead(const Position& head) const {
    switch (current) {
        case Direction::UP:    return Position(head.x - 1, head.y);
        case Direction::DOWN:  return Position(head.x + 1, head.y);
        case Direction::LEFT:  return Position(head.x, head.y - 1);
        case Direction::RIGHT: return Position(head.x, head.y + 1);
    }
}

bool Brain::isOpposite(Direction a, Direction b) const {
    return (a == Direction::UP    && b == Direction::DOWN)  ||
           (a == Direction::DOWN  && b == Direction::UP)    ||
           (a == Direction::LEFT  && b == Direction::RIGHT) ||
           (a == Direction::RIGHT && b == Direction::LEFT);
}
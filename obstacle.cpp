//obstacle placed on random positions
//causes game over on collision

#include "Obstacle.h"
#include <cstdlib>

Obstacle::Obstacle() {
    pos.x = rand() % 20;
    pos.y = rand() % 20;
}

Position Obstacle::getPosition() {
    return pos;
}

void Obstacle::draw() {
    // will be drawn in Board class
}

void Obstacle::update() {
    // obstacles don’t move (for now)
}
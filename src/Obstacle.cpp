//humna 

#include "Obstacle.h"
#include "raylib.h"
#include <cstdlib>

const int CELL_SIZE = 30;

Obstacle::Obstacle() {
    do {
        pos.x = rand() % 20;
        pos.y = rand() % 20;
    } while (pos.x >= 8 && pos.x <= 12 && pos.y >= 8 && pos.y <= 12);
}

Position Obstacle::getPosition() {
    return pos;
}

void Obstacle::update() {}

void Obstacle::draw() {
    int px = pos.x * CELL_SIZE;
    int py = pos.y * CELL_SIZE;
    DrawRectangle(px,     py,     CELL_SIZE,     CELL_SIZE,     DARKGRAY);
    DrawRectangle(px + 2, py + 2, CELL_SIZE - 4, CELL_SIZE - 4, GRAY);
}
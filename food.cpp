#include "Food.h"
#include <cstdlib>

Food::Food() {
    generate();
}

void Food::generate() {
    pos.x = rand() % 20;
    pos.y = rand() % 20;

    special = rand() % 2; // 0 or 1
}

Position Food::getPosition() {
    return pos;
}

bool Food::isSpecial() {
    return special;
}

void Food::draw() {
    // handled in Board.cpp
}

void Food::update() {
    // food doesn't move
}
#include "food.h"

Food::Food(int boardRows, int boardCols)
    : pos(1, 1), type(NORMAL), boardRows(boardRows), 
      boardCols(boardCols), specialTimer(0) {
    randomize();
}

void Food::randomize() {
    do {
        pos = Position(rand() % (boardCols - 2) + 1, 
                       rand() % (boardRows - 2) + 1);
    } while (pos.x == 10 && pos.y == 10); // avoid snake start

    type = (rand() % 4 == 0) ? SPECIAL : NORMAL;
    specialTimer = 20;
}

void Food::update() {
    if (type == SPECIAL) {
        specialTimer--;
        if (specialTimer <= 0)
            respawn();
    }
}

void Food::draw() {
    // Board handles cursor positioning
    // getSymbol() gives the character to print
}

void Food::respawn() {
    randomize();
}

Position Food::getPosition() const {
    return pos;
}

FoodType Food::getType() const {
    return type;
}

int Food::getPoints() const {
    return (type == SPECIAL) ? 5 : 1;
}

char Food::getSymbol() const {
    return (type == SPECIAL) ? '$' : '*';
}
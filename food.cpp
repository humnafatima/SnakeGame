#include "food.h"
#include "raylib.h"

const int FOOD_CELL = 30;

Food::Food(int boardRows, int boardCols)
    : pos(1, 1), type(NORMAL), boardRows(boardRows),
      boardCols(boardCols), specialTimer(0) {
    randomize();
}

void Food::randomize() {
    do {
        pos = Position(rand() % (boardCols - 2) + 1,
                       rand() % (boardRows - 2) + 1);
    } while (pos.x == 10 && pos.y == 10);

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
    int px = pos.x * FOOD_CELL;
    int py = pos.y * FOOD_CELL;

    if (type == SPECIAL) {
        // gold square for special food
        DrawRectangle(px + 2, py + 2, FOOD_CELL - 4, FOOD_CELL - 4, GOLD);
        DrawText("$", px + 8, py + 6, 20, WHITE);
    } else {
        // red circle for normal food
        DrawCircle(px + FOOD_CELL/2, py + FOOD_CELL/2,
                   FOOD_CELL/2 - 3, RED);
    }
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
    return (type == SPECIAL) ? 20 : 10;
}

char Food::getSymbol() const {
    return (type == SPECIAL) ? '$' : '*';
}
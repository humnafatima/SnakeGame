#include "Board.h"
#include "raylib.h"

void Board::drawGrid() {

    for (int i = 0; i <= 600; i += 30) {

        DrawLine(i, 0, i, 600, DARKGRAY);

        DrawLine(0, i, 600, i, DARKGRAY);
    }
}
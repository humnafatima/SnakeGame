#include "Board.h"
#include "raylib.h"

void Board::drawGrid() {
    for (int i = 0; i <= 800; i += 30) {
        DrawLine(i, 0, i, 800, DARKGRAY);
        DrawLine(0, i, 800, i, DARKGRAY);
    }
}
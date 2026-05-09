#include "raylib.h"
#include "GameController.h"

int main() {
    const int COLS      = 20;
    const int ROWS      = 20;
    const int CELL_SIZE = 30;

    const int SCREEN_W  = COLS * CELL_SIZE + 160;
    const int SCREEN_H  = ROWS * CELL_SIZE;

    InitWindow(SCREEN_W, SCREEN_H, "Snake Game — OOP Project");
    SetTargetFPS(60);

    GameController game(COLS, ROWS, CELL_SIZE);

    while (game.isRunning()) {
        game.handleInput();
        game.update(GetFrameTime());

        BeginDrawing();
        game.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
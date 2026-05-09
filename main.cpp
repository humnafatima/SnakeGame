#include "raylib.h"
#include "GameController.h"

int main() {
    InitWindow(800, 800, "Snake Game");
    SetTargetFPS(7);

    GameController game;

    while (!WindowShouldClose()) {
        game.handleMenuInput();
        game.update();
        BeginDrawing();
        ClearBackground(BLACK);
        game.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
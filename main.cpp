#include "raylib.h"
#include "GameController.h"

int main() {
    InitWindow(600, 600, "Snake Game");
    SetTargetFPS(10);

    GameController game;

    while (!WindowShouldClose()) {
        game.update();
        BeginDrawing();
        ClearBackground(BLACK);
        game.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
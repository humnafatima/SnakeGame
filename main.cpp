#include "raylib.h"
#include "snake.h"

const int cellSize = 20;
const int screenWidth = 800;
const int screenHeight = 600;

int main() {

    InitWindow(screenWidth, screenHeight, "Snake Test");
    SetTargetFPS(10);

    Snake snake;

    while (!WindowShouldClose()) {

        // INPUT
        if (IsKeyPressed(KEY_W)) snake.changeDirection(UP);
        if (IsKeyPressed(KEY_S)) snake.changeDirection(DOWN);
        if (IsKeyPressed(KEY_A)) snake.changeDirection(LEFT);
        if (IsKeyPressed(KEY_D)) snake.changeDirection(RIGHT);

        // UPDATE
        snake.move();

        // DRAW
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto& segment : snake.getBody()) {
            DrawRectangle(
                segment.x * cellSize,
                segment.y * cellSize,
                cellSize,
                cellSize,
                GREEN
            );
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
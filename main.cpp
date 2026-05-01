#include "raylib.h"

int main() {
    InitWindow(800, 600, "Raylib Test");   // Create a window
    while (!WindowShouldClose()) {          // Main loop
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();                          // Close window
    return 0;
}
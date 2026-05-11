//entry point 

#include "raylib.h"
#include "GameController.h"

int main() {
    InitWindow(800, 800, "SERPENT ARENA"); //creates game window 
    SetTargetFPS(7); //7 frames per second

    GameController game;

    while (!WindowShouldClose()) { //game keeps running until player closes window 
        game.handleMenuInput(); //start game, pause, choose mode
        game.update(); //updates all game logic
        BeginDrawing();
        ClearBackground(BLACK);
        game.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
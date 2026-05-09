#include "GameController.h"
#include "raylib.h"

GameController::GameController() : food(20, 20) {
    gameOver = false;
    score = 0;
    for (int i = 0; i < 5; i++) {
        obstacles.push_back(Obstacle());
    }
}

void GameController::update() {
    if (gameOver) return;

    snake.update();
    Position head = snake.getHead();

    if (head == food.getPosition()) {
        snake.grow();
        score += food.getPoints();  
        food.respawn();         
    }

    food.update();

    if (head.x < 0 || head.x >= 20 || head.y < 0 || head.y >= 20) {
        gameOver = true;
    }

    if (snake.checkSelfCollision()) {
        gameOver = true;
    }

    for (int i = 0; i < obstacles.size(); i++) {
        if (head == obstacles[i].getPosition()) {
            gameOver = true;
        }
    }
}

void GameController::draw() {
    board.drawGrid();
    snake.draw();
    food.draw();
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].draw();
    }
    DrawText(TextFormat("Score: %i", score), 10, 10, 20, WHITE);
    if (gameOver) {
        DrawText("GAME OVER", 180, 280, 40, RED);
        DrawText("Close and rerun to play again", 130, 330, 20, WHITE);
    }
}
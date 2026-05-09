#pragma once
#include "snake.h"
#include "food.h"
#include "obstacle.h"
#include "board.h"

enum class GameState { MENU, PLAYING, GAME_OVER };

class GameController {
private:
    Board      board;
    Snake      snake;
    Food       food;
    Obstacle   obstacle;

    int        score;
    int        highScore;
    GameState  state;

    int        cols;
    int        rows;
    int        cellSize;

    float      moveTimer;
    float      moveInterval;

    void  checkFoodCollision();
    void  checkObstacleCollision();
    void  resetGame();
    void  drawHUD()      const;
    void  drawMenu()     const;
    void  drawGameOver() const;

public:
    GameController(int cols, int rows, int cellSize);

    void handleInput();
    void update(float deltaTime);
    void draw()  const;

    bool isRunning() const;
};
#pragma once
#include "snake.h"
#include "food.h"
#include "obstacle.h"
#include "board.h"
#include <vector>

class GameController {
private:
    Snake snake;
    Food food;
    std::vector<Obstacle> obstacles;
    Board board;
    bool gameOver;
    int score;

public:
    GameController();
    void update();
    void draw();
    bool isGameOver() const { return gameOver; }
};
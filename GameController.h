#pragma once

#include "snake.h"

#include "food.h"

#include "obstacle.h"

#include "board.h"

#include <vector>

 

class GameController {

private:

    Snake snake1;

    Snake snake2;

    Food food;

    std::vector<Obstacle> obstacles;

    Board board;

    bool gameOver;

    int score1, score2;

    int winner;  // 1, 2, or 0 for draw

 

    void reshuffleObstacles();

 

public:

    GameController();

    void update();

    void draw();

    bool isGameOver() const { return gameOver; }

};
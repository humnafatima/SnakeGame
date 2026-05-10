//neha

#pragma once
#include "snake.h"
#include "food.h"
#include "obstacle.h"
#include <vector>

enum class GameMode { MENU, COUNTDOWN, ONE_PLAYER, TWO_PLAYER };
enum class GameState { PLAYING, GAME_OVER };

class GameController {
private:
    Snake snake1;
    Snake snake2;
    Food food;
    std::vector<Obstacle> obstacles;
    bool gameOver;
    int score1, score2;
    int winner;
    GameMode mode;
    GameState state;
    float countdownTimer;

    void reshuffleObstacles();
    void updateAI();
    Direction getAIDirection();
    void resetGame(); //reset game 

public:
    GameController();
    void update();
    void draw();
    void handleMenuInput();
    bool isGameOver() const { return gameOver; }
};
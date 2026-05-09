#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include<vector>
#include "Snake.h"
#include "Food.h"
#include "Obstacle.h"
#include "Board.h"
 class GameController{
private:
Snake snake;
Food food;
Board board;
std::vector<Obstacle>obstacles;
bool gameOver;
int score;
public:
GameController();
void update();
void draw();
bool isGameOver();
 };
#endif
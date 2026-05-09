//aleeza

#pragma once
#include "GameObject.h"
#include "snake.h"
#include <cstdlib>

enum FoodType { NORMAL, SPECIAL };

class Food : public GameObject {
public:
    Food(int boardRows, int boardCols);

    void draw() override;
    void update() override;

    Position getPosition() const;
    FoodType getType() const;
    int getPoints() const;
    void respawn();
    char getSymbol() const;

private:
    Position pos;
    FoodType type;
    int boardRows, boardCols;
    int specialTimer;

    void randomize();
};
//aleeza

#pragma once //prevents file from being included twice 
#include "GameObject.h" //base class - will inherit draw() and update()
#include "snake.h" //for position
#include <cstdlib>

enum FoodType { NORMAL, SPECIAL }; //normal 0 special 1 

class Food : public GameObject {
public:
    Food(int boardRows, int boardCols);

    //inherited
    void draw() override;
    void update() override;

    //new (5) - pos, type, points, respawn, symbol
    Position getPosition() const;
    FoodType getType() const;
    int getPoints() const;
    void respawn();
    char getSymbol() const;

private:
    Position pos;
    FoodType type;
    int boardRows, boardCols; //when randomize picks a new position it needs to know boundaries 
    int specialTimer;

    void randomize();
};
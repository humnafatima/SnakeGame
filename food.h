#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"
#include "Position.h"

class Food : public GameObject {
private:
    Position pos;
    bool special; // true = special food

public:
    Food();

    void generate();
    Position getPosition();
    bool isSpecial();

    void draw() override;
    void update() override;
};

#endif
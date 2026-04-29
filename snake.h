//snake.h: class definition

#ifndef SNAKE_H
#define SNAKE_H

#include "GameObject.h"

class Snake : public GameObject {
public:
    void draw() override;
    void update() override;
};

#endif
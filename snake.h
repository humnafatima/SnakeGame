//snake.h: class definition

#pragma once

#include "GameObject.h"

class Snake : public GameObject {
public:
    void draw() override;
    void update() override;
};
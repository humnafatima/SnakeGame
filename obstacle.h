//humna

#pragma once

#include "GameObject.h"
#include "Position.h"
//inherited from gameobject
class Obstacle : public GameObject {
private:
    Position pos; //stores where the obstacle is on baord 

public:
    Obstacle(); //will randomly place obsatcle in cpp

    Position getPosition(); //used for collision detection

    void draw() override;
    void update() override;
};
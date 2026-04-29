#ifndef OBSTACLE_H
#define OBSTACLE_H //dont understand these lines yet hence not written in every part 

#include "GameObject.h"
#include "Position.h"

class Obstacle : public GameObject {
private:
    Position pos; //stores where the obstacle is on baord 

public:
    Obstacle(); //will randomly place obsatcle in cpp

    Position getPosition(); //used for collision detection

    void draw() override;
    void update() override;
};

#endif
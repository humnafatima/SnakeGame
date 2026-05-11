//humna - declarations: header file blueprint of the snake class, tells these variables and functions exist 

#pragma once //prevenys the header file from being included multiple times (only include this file once)
#include <raylib.h> //needed for colour since its a raylib type
#include "Position.h" //imports postion class needed to to store snake body 
#include "GameObject.h" //snake inherits from gameobject (snake gets polymorphism, virtual functions and shared game object structure)
#include <list>

enum Direction { UP, DOWN, LEFT, RIGHT }; //creates a custom type called direction

class Snake : public GameObject {
private:
    std::list<Position> body; //stores snake segments
    Direction dir; //current dir
    Direction nextDir; //upcoming (prevents weird instant reversals during input)
    bool growing; //tracks whether snake should grow next update 
    int upKey, downKey, leftKey, rightKey;  // customizable controls

public:
    Snake();
    Snake(int startX, int startY, int upKey, int downKey, int leftKey, int rightKey); //custom constructor (lets you choose spawn positions and choose controls)

    const std::list<Position>& getBody() const; //retruns snake body safely and caller cannot modify body coz of const

    // Rule of Three (when gameController resets the game it reassigns snake objects)
    Snake(const Snake& other); //copy constructor 
    Snake& operator=(const Snake& other); //assignment operator 
    //destrcutor is handled by std::list automatically 

    bool operator==(const Snake& other) const; //equality operator 

    void update() override; //handles input movement growth
    void draw () override;
    void draw(Color headColor, Color bodyColor);  // each player different color
    void grow(); //makes snow grow next update
    bool checkSelfCollision() const; //did snake hit itself
    bool collidesWithOther(const Snake& other) const;  // 2 player collision
    Position getHead() const; //returns head position
    Direction getDirection() const { //returns current dir
        return dir; 
    }
    void changeDirection(Direction newDir); //changes dir safely 
    bool containsPosition(const Position& p) const; //checks whether snake occupies a certain cell, needed for food spawning and collision checking 
    std::list<Position>& getBody(); //allows modifying body directly
    int getLength() const { //returns snake length
        return (int)body.size(); 
    }
};
/* 
DATA
snake body
direction
controls
growth state

BEHAVIOR
move
draw
grow
collision detection

OOP FEATURES
abstract class:(gameobject.h), pure virtual draw() and update() force all game objects to implement them 
inheritance: (snake, food, obstacle) all inherit from GameObject, getting the interface
polymorphism: same function name(draw), completely different behaviour per object 
encapsulation: private data, public methods only
operator overloading: (position, snake) ==lets us compare positions naturally for collision
Rule of Three: (snake.cpp) copy constructor and assignment for safe copying of snake 
*/
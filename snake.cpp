//implemnations - humna 

#include "snake.h" 
#include "raylib.h" //graphics 

const int CELL = 30; //a snake “block” is drawn as a 30×30 square.

Position::Position(int x, int y) : x(x), y(y) {} //constructor

bool Position::operator==(const Position& other) const { //overloads == operator
    return x == other.x && y == other.y; //two positions are equal if both x and y match 
}

bool Position::operator!=(const Position& other) const { 
    return !(*this == other); //if not equal return true 
}

// Default constructor — player 1 WASD
Snake::Snake() : dir(RIGHT), nextDir(RIGHT), growing(false),
    upKey(KEY_W), downKey(KEY_S), leftKey(KEY_A), rightKey(KEY_D) {
    
    body.push_back(Position(5, 10)); //head at (5, 10)
    body.push_back(Position(4, 10));
    body.push_back(Position(3, 10));
}

// Custom constructor — set start pos and keys
Snake::Snake(int startX, int startY, int uk, int dk, int lk, int rk)
    : dir(RIGHT), nextDir(RIGHT), growing(false),
      upKey(uk), downKey(dk), leftKey(lk), rightKey(rk) {
    body.push_back(Position(startX,     startY));
    body.push_back(Position(startX - 1, startY));
    body.push_back(Position(startX - 2, startY));
}

Snake::Snake(const Snake& other) //copy constructor, copies everything from other snake 
    : body(other.body), dir(other.dir), nextDir(other.nextDir),
      growing(other.growing), upKey(other.upKey), downKey(other.downKey),
      leftKey(other.leftKey), rightKey(other.rightKey) {}

Snake& Snake::operator=(const Snake& other) { //assignment operator (=)
    if (this == &other) return *this; //prevent self assignment 
    body     = other.body;
    dir      = other.dir;
    nextDir  = other.nextDir;
    growing  = other.growing;
    upKey    = other.upKey;
    downKey  = other.downKey;
    leftKey  = other.leftKey;
    rightKey = other.rightKey;
    return *this; //returns current object 
}

bool Snake::operator==(const Snake& other) const { //Two snakes are equal if their heads are in same position only.
    return getHead() == other.getHead();
}

void Snake::changeDirection(Direction newDir) { //changes snake direction
    if ((dir == UP    && newDir == DOWN)  || //prevents reversing directly 
        (dir == DOWN  && newDir == UP)    ||
        (dir == LEFT  && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) 
        return;
    nextDir = newDir; //stores new direction for next update 
}

void Snake::update() { //update function; this is the core game loop logic 
    if (IsKeyPressed(upKey)    && dir != DOWN)  nextDir = UP; //if w is pressed, go up (but only if not currently going down- prevents reverse)
    if (IsKeyPressed(downKey)  && dir != UP)    nextDir = DOWN;
    if (IsKeyPressed(leftKey)  && dir != RIGHT) nextDir = LEFT;
    if (IsKeyPressed(rightKey) && dir != LEFT)  nextDir = RIGHT;

    dir = nextDir; //actual movement direction is updated

    Position head = body.front(); //take current head 

    if (dir == UP)    head.y--; //move head by 1 grid cell
    if (dir == DOWN)  head.y++;
    if (dir == LEFT)  head.x--;
    if (dir == RIGHT) head.x++;

    body.push_front(head); //new head becomes front of list 

    if (growing) { growing = false; } //is snake ate food: dont remove tail, snake grows
    else { body.pop_back(); } //otherwise remove last segment, basically normal movement 
}

void Snake::grow() { //sets flag so next update inceases length 
    growing = true; 
}

bool Snake::checkSelfCollision() const {
    Position head = body.front(); //get head

    auto it = body.begin(); ++it; //skip head, start checjing from second segment 

    for (; it != body.end(); ++it) //already did initialization in the above line, only condition is needed now 
        if (*it == head) return true; //if head tocuehd body, collision
    return false;
}

bool Snake::collidesWithOther(const Snake& other) const { //collision with other snake 

    Position head = body.front(); //get head

    for (const auto& seg : other.getBody()) //loop through other snake body 
        if (seg == head) return true; //if head touces any segment, collision
    return false;
}

Position Snake::getHead() const { //utility functions, returns head position
    return body.front(); 
}

bool Snake::containsPosition(const Position& p) const { //check if snake occupies a given grid cell
    for (const auto& seg : body)
        if (seg == p) return true;
    return false;
}

std::list<Position>& Snake::getBody() { //retruns body (chnageable verison)
    return body; 
}

// Need const version for collidesWithOther
const std::list<Position>& Snake::getBody() const { //retruns body (read only version)
    return body; 
}

void Snake::draw() {
    draw(GREEN, (Color){34, 139, 34, 255});  // default colors
}

void Snake::draw(Color headColor, Color bodyColor) { //ahh drawing the snake part using raylib ofc 
    bool isHead = true; //first segment is treated as head 

    for (const auto& seg : body) { //loop through each segment

        int px = seg.x * CELL; //convert grid position - pixel position
        int py = seg.y * CELL;

        if (isHead) { 
            DrawRectangle(px + 1, py + 1, CELL - 2, CELL - 2, headColor); //draws head slightly inset for border effect 
            int e = CELL / 6;
            switch (dir) { //draws eyes based on direction
                case RIGHT:
                    DrawRectangle(px + CELL*3/4, py + CELL/4,   e, e, WHITE); //positions tiny squares = eyes 
                    DrawRectangle(px + CELL*3/4, py + CELL*2/3, e, e, WHITE);
                    break;
                case LEFT:
                    DrawRectangle(px + CELL/6,   py + CELL/4,   e, e, WHITE);
                    DrawRectangle(px + CELL/6,   py + CELL*2/3, e, e, WHITE);
                    break;
                case UP:
                    DrawRectangle(px + CELL/4,   py + CELL/6,   e, e, WHITE);
                    DrawRectangle(px + CELL*2/3, py + CELL/6,   e, e, WHITE);
                    break;
                case DOWN:
                    DrawRectangle(px + CELL/4,   py + CELL*3/4, e, e, WHITE);
                    DrawRectangle(px + CELL*2/3, py + CELL*3/4, e, e, WHITE);
                    break;
            }
            isHead = false;
        } else {
            DrawRectangle(px + 2, py + 2, CELL - 4, CELL - 4, bodyColor); //slightly smaller rectangles for body segnments 
        }
    }
}

/* Summary:
Snake movement (grid-based)
Input handling (Raylib keys)
Growth system (food mechanic)
Collision detection (self + other snake)
Rendering (head + body + eyes)

Deep C++ concepts:
operator overloading
copy constructor
assignment operator
const correctness
STL list usage
*/
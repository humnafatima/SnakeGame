#include "snake.h"
#include "raylib.h"

const int CELL = 30;

Position::Position(int x, int y) : x(x), y(y) {}
bool Position::operator==(const Position& other) const { return x == other.x && y == other.y; }
bool Position::operator!=(const Position& other) const { return !(*this == other); }

// Default constructor — player 1 WASD
Snake::Snake() : dir(RIGHT), nextDir(RIGHT), growing(false),
    upKey(KEY_W), downKey(KEY_S), leftKey(KEY_A), rightKey(KEY_D) {
    body.push_back(Position(5, 10));
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

Snake::Snake(const Snake& other)
    : body(other.body), dir(other.dir), nextDir(other.nextDir),
      growing(other.growing), upKey(other.upKey), downKey(other.downKey),
      leftKey(other.leftKey), rightKey(other.rightKey) {}

Snake& Snake::operator=(const Snake& other) {
    if (this == &other) return *this;
    body     = other.body;
    dir      = other.dir;
    nextDir  = other.nextDir;
    growing  = other.growing;
    upKey    = other.upKey;
    downKey  = other.downKey;
    leftKey  = other.leftKey;
    rightKey = other.rightKey;
    return *this;
}

bool Snake::operator==(const Snake& other) const {
    return getHead() == other.getHead();
}

void Snake::changeDirection(Direction newDir) {
    if ((dir == UP    && newDir == DOWN)  ||
        (dir == DOWN  && newDir == UP)    ||
        (dir == LEFT  && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) return;
    nextDir = newDir;
}

void Snake::update() {
    if (IsKeyPressed(upKey)    && dir != DOWN)  nextDir = UP;
    if (IsKeyPressed(downKey)  && dir != UP)    nextDir = DOWN;
    if (IsKeyPressed(leftKey)  && dir != RIGHT) nextDir = LEFT;
    if (IsKeyPressed(rightKey) && dir != LEFT)  nextDir = RIGHT;

    dir = nextDir;
    Position head = body.front();
    if (dir == UP)    head.y--;
    if (dir == DOWN)  head.y++;
    if (dir == LEFT)  head.x--;
    if (dir == RIGHT) head.x++;

    body.push_front(head);
    if (growing) { growing = false; }
    else { body.pop_back(); }
}

void Snake::grow() { growing = true; }

bool Snake::checkSelfCollision() const {
    Position head = body.front();
    auto it = body.begin(); ++it;
    for (; it != body.end(); ++it)
        if (*it == head) return true;
    return false;
}

bool Snake::collidesWithOther(const Snake& other) const {
    Position head = body.front();
    for (const auto& seg : other.getBody())
        if (seg == head) return true;
    return false;
}

Position Snake::getHead() const { return body.front(); }

bool Snake::containsPosition(const Position& p) const {
    for (const auto& seg : body)
        if (seg == p) return true;
    return false;
}

std::list<Position>& Snake::getBody() { return body; }

// Need const version for collidesWithOther
const std::list<Position>& Snake::getBody() const { return body; }

void Snake::draw(Color headColor, Color bodyColor) {
    bool isHead = true;
    for (const auto& seg : body) {
        int px = seg.x * CELL;
        int py = seg.y * CELL;
        if (isHead) {
            DrawRectangle(px + 1, py + 1, CELL - 2, CELL - 2, headColor);
            int e = CELL / 6;
            switch (dir) {
                case RIGHT:
                    DrawRectangle(px + CELL*3/4, py + CELL/4,   e, e, WHITE);
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
            DrawRectangle(px + 2, py + 2, CELL - 4, CELL - 4, bodyColor);
        }
    }
}
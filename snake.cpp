#include "snake.h"
#include "raylib.h"

const int CELL = 30;  // cell size defined here since it's not in constructor anymore

// Position implementation
Position::Position(int x, int y) : x(x), y(y) {}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}

// ── Constructor ───────────────────────────────
Snake::Snake() : dir(RIGHT), nextDir(RIGHT), growing(false) {
    body.push_back(Position(10, 10));
    body.push_back(Position(9,  10));
    body.push_back(Position(8,  10));
}

// ── Copy Constructor ──────────────────────────
Snake::Snake(const Snake& other)
    : body(other.body), dir(other.dir),
      nextDir(other.nextDir), growing(other.growing) {}

// ── Assignment Operator ───────────────────────
Snake& Snake::operator=(const Snake& other) {
    if (this == &other) return *this;
    body    = other.body;
    dir     = other.dir;
    nextDir = other.nextDir;
    growing = other.growing;
    return *this;
}

// ── Operator== ────────────────────────────────
bool Snake::operator==(const Snake& other) const {
    return getHead() == other.getHead();
}

// ── changeDirection ───────────────────────────
void Snake::changeDirection(Direction newDir) {
    if ((dir == UP    && newDir == DOWN)  ||
        (dir == DOWN  && newDir == UP)    ||
        (dir == LEFT  && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) return;
    nextDir = newDir;
}

// ── update ────────────────────────────────────
void Snake::update() {
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    && dir != DOWN)  nextDir = UP;
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  && dir != UP)    nextDir = DOWN;
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))  && dir != RIGHT) nextDir = LEFT;
    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && dir != LEFT)  nextDir = RIGHT;

    dir = nextDir;

    Position head = body.front();
    if (dir == UP)    head.y--;
    if (dir == DOWN)  head.y++;
    if (dir == LEFT)  head.x--;
    if (dir == RIGHT) head.x++;

    body.push_front(head);
    if (growing) {
        growing = false;
    } else {
        body.pop_back();
    }
}

// ── grow ──────────────────────────────────────
void Snake::grow() {
    growing = true;
}

// ── checkSelfCollision ────────────────────────
bool Snake::checkSelfCollision() const {
    Position head = body.front();
    auto it = body.begin();
    ++it;
    for (; it != body.end(); ++it)
        if (*it == head) return true;
    return false;
}

// ── getHead ───────────────────────────────────
Position Snake::getHead() const {
    return body.front();
}

// ── containsPosition ──────────────────────────
bool Snake::containsPosition(const Position& p) const {
    for (const auto& seg : body)
        if (seg == p) return true;
    return false;
}

// ── getBody ───────────────────────────────────
std::list<Position>& Snake::getBody() {
    return body;
}

// ── draw ──────────────────────────────────────
void Snake::draw() {
    bool isHead = true;
    for (const auto& seg : body) {
        int px = seg.x * CELL;
        int py = seg.y * CELL;
        if (isHead) {
            DrawRectangle(px + 1, py + 1, CELL - 2, CELL - 2, GREEN);
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
            DrawRectangle(px + 2, py + 2, CELL - 4, CELL - 4, (Color){34, 139, 34, 255});
        }
    }
}
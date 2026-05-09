#include "snake.h"
#include "raylib.h"
#include <stdexcept>
#include "snake.h"
#include "raylib.h"
#include <stdexcept>
#include <list>

// Position implementation (defined here, not in Position.cpp)
Position::Position(int x, int y) : x(x), y(y) {}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}

// Then all your Snake methods below...
// ── Constructor ───────────────────────────────────────────────────────────────
Snake::Snake(int startX, int startY, int cs, int initialLength)
    : dir(RIGHT), nextDir(RIGHT),
      growing(false), alive(true), cellSize(cs)
{
    // Build snake horizontally: head at (startX, startY),
    // body extends left.
    for (int i = 0; i < initialLength; ++i)
        body.push_back(Position(startX - i, startY));
}

// ── Copy constructor ──────────────────────────────────────────────────────────
Snake::Snake(const Snake& other)
    : body(other.body),
      dir(other.dir),
      nextDir(other.nextDir),
      growing(other.growing),
      alive(other.alive),
      cellSize(other.cellSize)
{}

// ── Assignment operator ───────────────────────────────────────────────────────
Snake& Snake::operator=(const Snake& other) {
    if (this == &other) return *this;
    body     = other.body;
    dir      = other.dir;
    nextDir  = other.nextDir;
    growing  = other.growing;
    alive    = other.alive;
    cellSize = other.cellSize;
    return *this;
}

// ── Operator== (compare head positions) ──────────────────────────────────────
bool Snake::operator==(const Snake& other) const {
    return getHeadPosition() == other.getHeadPosition();
}

// ── handleInput ───────────────────────────────────────────────────────────────
// Buffers the next direction; prevents 180° reversal.
void Snake::handleInput() {
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    && dir != DOWN)  nextDir = UP;
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  && dir != UP)    nextDir = DOWN;
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))  && dir != RIGHT) nextDir = LEFT;
    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && dir != LEFT)  nextDir = RIGHT;
}

// ── update (move one step) ────────────────────────────────────────────────────
void Snake::update() {
    if (!alive) return;

    dir = nextDir;   // commit buffered direction

    Position head = body.front();
    switch (dir) {
        case UP:    head.y--; break;
        case DOWN:  head.y++; break;
        case LEFT:  head.x--; break;
        case RIGHT: head.x++; break;
    }

    body.push_front(head);   // new head

    if (growing) {
        growing = false;     // keep tail → snake grew by 1
    } else {
        body.pop_back();     // remove tail → constant length
    }

    if (isSelfCollision()) alive = false;
}

// ── grow ──────────────────────────────────────────────────────────────────────
void Snake::grow() {
    growing = true;
}

// ── checkWallCollision ────────────────────────────────────────────────────────
void Snake::checkWallCollision(int cols, int rows) {
    Position h = getHeadPosition();
    if (h.x < 0 || h.x >= cols || h.y < 0 || h.y >= rows)
        alive = false;
}

// ── isSelfCollision ───────────────────────────────────────────────────────────
bool Snake::isSelfCollision() const {
    if (body.size() <= 1) return false;
    Position head = body.front();
    auto it = body.begin();
    ++it;   // skip head
    for (; it != body.end(); ++it)
        if (*it == head) return true;
    return false;
}

// ── containsPosition ─────────────────────────────────────────────────────────
bool Snake::containsPosition(const Position& p) const {
    for (const auto& seg : body)
        if (seg == p) return true;
    return false;
}

// ── getHeadPosition ───────────────────────────────────────────────────────────
Position Snake::getHeadPosition() const {
    if (body.empty()) throw std::runtime_error("Snake body is empty.");
    return body.front();
}

// ── draw ──────────────────────────────────────────────────────────────────────
void Snake::draw() {
    bool isHead = true;
    for (const auto& seg : body) {
        int px = seg.x * cellSize;
        int py = seg.y * cellSize;

        if (isHead) {
            // Head — bright green
            DrawRectangle(px + 1, py + 1, cellSize - 2, cellSize - 2, GREEN);

            // Eyes — small white squares, position depends on direction
            int e = cellSize / 6;
            switch (dir) {
                case RIGHT:
                    DrawRectangle(px + cellSize*3/4, py + cellSize/4,   e, e, WHITE);
                    DrawRectangle(px + cellSize*3/4, py + cellSize*2/3, e, e, WHITE);
                    break;
                case LEFT:
                    DrawRectangle(px + cellSize/6,   py + cellSize/4,   e, e, WHITE);
                    DrawRectangle(px + cellSize/6,   py + cellSize*2/3, e, e, WHITE);
                    break;
                case UP:
                    DrawRectangle(px + cellSize/4,   py + cellSize/6,   e, e, WHITE);
                    DrawRectangle(px + cellSize*2/3, py + cellSize/6,   e, e, WHITE);
                    break;
                case DOWN:
                    DrawRectangle(px + cellSize/4,   py + cellSize*3/4, e, e, WHITE);
                    DrawRectangle(px + cellSize*2/3, py + cellSize*3/4, e, e, WHITE);
                    break;
            }
            isHead = false;
        } else {
            // Body — darker green
            DrawRectangle(px + 2, py + 2, cellSize - 4, cellSize - 4,
                          (Color){34, 139, 34, 255});
        }
    }
}
#pragma once
#include "GameObject.h"
#include "Position.h"
#include <list>

// ── Direction ────────────────────────────────────────────────────────────────
enum Direction { UP, DOWN, LEFT, RIGHT };

// ── Snake ────────────────────────────────────────────────────────────────────
// Uses std::list<Position> as the linked-list data structure for the body.
// Inherits from GameObject (satisfies abstract class / inheritance requirement).

class Snake : public GameObject {
private:
    std::list<Position> body;   // linked list — head is front, tail is back
    Direction           dir;
    Direction           nextDir;
    bool                growing;    // if true, don't pop tail on next move
    bool                alive;
    int                 cellSize;

    bool isSelfCollision() const;

public:
    // Constructor / Destructor
    Snake(int startX, int startY, int cellSize, int initialLength = 3);
    ~Snake() override = default;

    // Copy constructor & assignment operator  (Rule of Three)
    Snake(const Snake& other);
    Snake& operator=(const Snake& other);

    // Operator overload  (required by project spec)
    bool operator==(const Snake& other) const;  // compares head positions

    // GameObject interface
    void draw()   override;
    void update() override;

    // Game logic
    void handleInput();
    void grow();

    // Queries
    Position                    getHeadPosition() const;
    const std::list<Position>&  getBody()         const { return body; }
    bool                        isAlive()         const { return alive; }
    int                         getLength()       const { return (int)body.size(); }
    Direction                   getDirection()    const { return dir; }
    bool                        containsPosition(const Position& p) const;

    // Wall-collision check (called by GameController)
    void checkWallCollision(int cols, int rows);
};
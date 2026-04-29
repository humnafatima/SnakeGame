//GameObject provides abstraction by defining a common interface for all game elements.
//It enables polymorphism so different objects can be treated uniformly.

class GameObject { //any object in the game MUST have:
public:
    virtual void draw() = 0; //how it appears
    virtual void update() = 0; //how it behaves 
    virtual ~GameObject() {}
};
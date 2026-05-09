#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class GameObject {
public:
    virtual void draw() = 0; 
    virtual void update() = 0;
    virtual ~GameObject() {

    }
}; 
#endif
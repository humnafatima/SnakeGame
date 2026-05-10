//abstarct base class - top of heirarchy 
//oop: abstract class and pure virtual functions (snake food and obstacle all inherit from gameobject)

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class GameObject {
public:
    virtual void draw() = 0; 
    virtual void update() = 0;
    virtual ~GameObject() {}
}; 
#endif
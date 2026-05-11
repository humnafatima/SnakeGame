//neha
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

//virtual destrcutor is need to ensure that derived class's destructor is called when an object is called through a pointer
//if it wasnt there the program will only execute the base class destrcutor 
//problems: memory leak (if the derived class allocated heap memory that never gets freed)
//undefined behaviour (deleting a dervied object througha non-virtual base class destrcutor)
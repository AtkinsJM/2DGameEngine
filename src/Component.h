#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Entity;

class Component
{
    public:
        std::string componentName;
        Entity* owner;
        virtual ~Component() {};
        virtual void Initialise() {};
        virtual void Update(float deltaTime) {};
        virtual void Render() {};

    private:
};

#endif
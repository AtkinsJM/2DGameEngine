#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"


#include <iostream>

Entity::Entity(EntityManager& manager) :  entityManager(manager)
{
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) :  entityManager(manager), entityName(name)
{
    this->isActive = true;
}

void Entity::Update(float deltaTime)
{
    for(auto &component : components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render()
{
    for(auto &component : components)
    {
        component->Render();
    }
}

void Entity::Destroy()
{
    this->isActive = false;
}

void Entity::DisplayInfo()
{
    std::cout << "\nEntity name: " << entityName << std::endl;
    if(components.size() == 0) { return; }
    for(auto &component : components)
    {
        std::cout << "\tComponent<" << component->componentName << ">" << std::endl;
    }
}
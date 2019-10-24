#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"
#include "Components/ColliderComponent.h"


#include <iostream>
#include <algorithm>

Entity::Entity(EntityManager& manager) :  entityManager(manager)
{
    this->bIsActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer) :  entityManager(manager), entityName(name), layer(layer)
{
    this->bIsActive = true;
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
    this->bIsActive = false;
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

void Entity::CheckCollisions()
{
    if(!bIsActive || !GetComponent<ColliderComponent>()) { return; }
    // Get tags of all colliders in collision with entity
    std::vector<Entity*> collisionEntities = entityManager.GetEntityCollisions(this);
    for(auto otherEntity : collisionEntities)
    {
        // If started colliding with entity
        if(std::find(currentCollisions.begin(), currentCollisions.end(), otherEntity) == currentCollisions.end())
        {
            OnBeginCollision(otherEntity);
        }
        else
        {
            OnContinueCollision(otherEntity);
        }
    }
    for(auto otherEntity : currentCollisions)
    {
         // If ended colliding with entity
        if(std::find(collisionEntities.begin(), collisionEntities.end(), otherEntity) == collisionEntities.end())
        {
            OnEndCollision(otherEntity);
        }
    }
    currentCollisions = collisionEntities;

}

void Entity::OnBeginCollision(Entity* otherEntity)
{
    std::cout << entityName << " started colliding with " << otherEntity->EntityName() << std::endl;
    if(GetComponent<ColliderComponent>()->colliderType == ColliderType::PLAYER && otherEntity->GetComponent<ColliderComponent>()->colliderType == ColliderType::ENEMY)
    {
        std::cout << "Game over!" << std::endl;
    }
    else if (GetComponent<ColliderComponent>()->colliderType == ColliderType::PLAYER && otherEntity->GetComponent<ColliderComponent>()->colliderType == ColliderType::PROJECTILE_ENEMY)
    {
        otherEntity->Destroy();
        std::cout << "Take damage!" << std::endl;
        
    }
}

void Entity::OnContinueCollision(Entity* otherEntity)
{
    std::cout << entityName << " still colliding with " << otherEntity->EntityName() << std::endl;
}

void Entity::OnEndCollision(Entity* otherEntity)
{
    std::cout << entityName << " ended colliding with " << otherEntity->EntityName() << std::endl;
}
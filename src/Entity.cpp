#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"
#include "Components/ColliderComponent.h"
#include "Components/PlayerComponent.h"


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

void Entity::InitialiseComponents()
{
    for(auto &component : components)
    {
        component->Initialise();
    }
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
    
    if(GetComponent<ColliderComponent>()->colliderType == ColliderType::PLAYER && otherEntity->GetComponent<ColliderComponent>()->colliderType == ColliderType::ENEMY)
    {
        // Player lose life
        PlayerComponent* player = GetComponent<PlayerComponent>();
        if(player)
        {
            player->LoseLife();
        }
    }
    else if (GetComponent<ColliderComponent>()->colliderType == ColliderType::PLAYER && otherEntity->GetComponent<ColliderComponent>()->colliderType == ColliderType::PROJECTILE_ENEMY)
    {
        // Player lose life
        PlayerComponent* player = GetComponent<PlayerComponent>();
        if(player)
        {
            player->LoseLife();
        }
        otherEntity->Destroy();
        
    }
    else if (GetComponent<ColliderComponent>()->colliderType == ColliderType::ENEMY && otherEntity->GetComponent<ColliderComponent>()->colliderType == ColliderType::PROJECTILE_PLAYER)
    {
        otherEntity->Destroy();
        Destroy();
    }
}

void Entity::OnContinueCollision(Entity* otherEntity)
{

}

void Entity::OnEndCollision(Entity* otherEntity)
{

}
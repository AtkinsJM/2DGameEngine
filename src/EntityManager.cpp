#include "EntityManager.h"
#include "Entity.h"
#include "Collision.h"
#include "Components/ColliderComponent.h"

void EntityManager::ClearData()
{
    for(auto &entity : entities)
    {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime)
{
    for(int i = 0; i < entities.size(); i++)
    {
        // Call update method on entity
        entities[i]->Update(deltaTime);
        // TODO: consider passing all collisions into this method straight away
        entities[i]->CheckCollisions();
        // If entity is inactive (destroyed), remove it
        if(entities[i]->IsActive() == false)
        {
            entities.erase(entities.begin() + i);
        }
    }
    /*
    for(auto &entity : entities)
    {
        entity->Update(deltaTime);
    }*/
}

void EntityManager::Render()
{
    for(int layerNum = 0; layerNum < NUM_LAYERS; layerNum++)
    {
        std::vector<Entity*> entitiesInLayer = GetEntitiesByLayer(static_cast<LayerType>(layerNum));
        for(auto &entity : entitiesInLayer)
        {
            entity->Render();
        }
    } 
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer)
{
    Entity* entity = new Entity(*this, entityName, layer);
    entities.push_back(entity);
    //entities.emplace_back(entity);
    return *entity;
}

void EntityManager::ListAllEntities()
{
    for(auto &entity : entities)
    {
        entity->DisplayInfo();
    }
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity*> entitiesInLayer;
    for(auto &entity : entities)
    {
        if(entity->layer == layer)
        {
            entitiesInLayer.push_back(entity);
        }
    }
    return entitiesInLayer;
}

std::vector<Entity*> EntityManager::GetEntityCollisions(Entity* myEntity) const
{
    std::vector<Entity*> collisionEntities;
    ColliderComponent* myCollider = myEntity->GetComponent<ColliderComponent>();
    if(!myCollider) { return collisionEntities; }
    for(auto &entity : entities)
    {
        //TODO: check equivalence relation
        if(entity != myEntity && entity->HasComponent<ColliderComponent>())
        {
            ColliderComponent* otherCollider = entity->GetComponent<ColliderComponent>();
            if(Collision::CheckRectangleCollision(myCollider->collider, otherCollider->collider) && Collision::CheckCollisionTypes(myCollider->colliderType, otherCollider->colliderType))
            {
                collisionEntities.emplace_back(otherCollider->owner);
            }
        }
    }
    return collisionEntities;
}
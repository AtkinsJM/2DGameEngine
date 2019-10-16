#include "EntityManager.h"
#include "Entity.h"

void EntityManager::ClearData()
{
    for(auto &entity : entities)
    {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime)
{
    for(auto &entity : entities)
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render()
{
    for(auto &entity : entities)
    {
        entity->Render();
    }
}

Entity& EntityManager::AddEntity(std::string entityName)
{
    Entity* entity = new Entity(*this, entityName);
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

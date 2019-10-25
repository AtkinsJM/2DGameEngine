#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <string>

#include "Constants.h"

class Entity;

class EntityManager
{
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasEntities() { return entities.size() > 0; };
        Entity& AddEntity(std::string entityName, LayerType layer);
        std::vector<Entity*> GetEntities() const { return entities; };
        std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
        unsigned int GetEntityCount() { return entities.size(); };
        void ListAllEntities();
        std::vector<Entity*> GetEntityCollisions(Entity* myEntity) const;
        Entity& Instantiate(Entity* prefab, int posX, int posY);
    private:
        std::vector<Entity*> entities;
};

#endif
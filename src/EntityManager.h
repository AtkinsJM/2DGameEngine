#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <string>

class Entity;

class EntityManager
{
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasEntities() { return entities.size() > 0; };
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const { return entities; };
        unsigned int GetEntityCount() { return entities.size(); };
        void ListAllEntities();

    private:
        std::vector<Entity*> entities;
};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

class EntityManager;
class Component;

class Entity
{
    public:
        std::string entityName;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const { return isActive; };

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            T* newComponent = new T(std::forward<TArgs>(args)...);
            newComponent->owner = this;
            components.push_back(newComponent);
            newComponent->Initialise();
            return *newComponent;
        }

    private:
        EntityManager& entityManager;
        bool isActive;
        std::vector<Component*> components;
};

#endif
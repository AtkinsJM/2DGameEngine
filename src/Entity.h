#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Constants.h"

class EntityManager;
class Component;
class ColliderComponent;

class Entity
{
    public:
        EntityManager& entityManager;
        LayerType layer;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name, LayerType layer);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const { return bIsActive; };
        void InitialiseComponents();

        void DisplayInfo();
        void CheckCollisions();
        std::string EntityName() { return entityName; };

        virtual void OnBeginCollision(Entity* otherEntity);
        virtual void OnContinueCollision(Entity* otherEntity);
        virtual void OnEndCollision(Entity* otherEntity);

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            T* newComponent = new T(std::forward<TArgs>(args)...);
            newComponent->owner = this;
            components.push_back(newComponent);
            componentTypeMap.emplace(&typeid(*newComponent), newComponent);
            //newComponent->Initialise();
            return *newComponent;
        }

        template<typename T>
        T* GetComponent()
        {
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }

        template<typename T>
        bool HasComponent()
        {
            return componentTypeMap[&typeid(T)];
        }

    private:
        std::string entityName;
        bool bIsActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
        // TODO: rename vector
        std::vector<Entity*> currentCollisions;
};

#endif
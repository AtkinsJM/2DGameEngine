#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Constants.h"

class EntityManager;
class Component;

class Entity
{
    public:
        std::string entityName;
        LayerType layer;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name, LayerType layer);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const { return isActive; };

        void DisplayInfo();

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            T* newComponent = new T(std::forward<TArgs>(args)...);
            newComponent->owner = this;
            components.push_back(newComponent);
            componentTypeMap.emplace(&typeid(*newComponent), newComponent);
            newComponent->Initialise();
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
        EntityManager& entityManager;
        bool isActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif
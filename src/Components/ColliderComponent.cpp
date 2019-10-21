#include "ColliderComponent.h"
#include "../Entity.h"
#include "TransformComponent.h"
#include "../Game.h"

ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height) 
{
    componentName = "ColliderComponent";
    this->colliderTag = colliderTag;
    this->collider = {x, y, width, height};
}

void ColliderComponent::Initialise() 
{
    transform = owner->GetComponent<TransformComponent>();
    if(!transform) { return; }
    sourceRect = {0, 0, transform->width, transform->height};
    destinationRect = {collider.x, collider.y, collider.w, collider.h};
}
        
void ColliderComponent::Update(float deltaTime)
{
    if(!transform) { return; }
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;

    destinationRect.x = collider.x - Game::camera.x;
    destinationRect.y = collider.y - Game::camera.y;
}

void ColliderComponent::Render()
{
   
}
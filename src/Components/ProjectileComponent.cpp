#include "ProjectileComponent.h"
#include "../Entity.h"
#include "TransformComponent.h"
#include <iostream>

ProjectileComponent::ProjectileComponent(int speed, int range, float angleRad)
{
    componentName = "ProjectileComponent";
    this->speed = speed;
    this->range = range;
    this->angleRad = angleRad;
}

void ProjectileComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    if(!transform) { return; }
    origin = glm::vec2(transform->position.x, transform->position.y);
    transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
    std::cout << transform->velocity.x << ", " << transform->velocity.y << std::endl;
}

void ProjectileComponent::Update(float deltaTime)
{
    if(glm::distance(transform->position, origin) > range)
    {
        owner->Destroy();
    }
}

void ProjectileComponent::Render()
{

}
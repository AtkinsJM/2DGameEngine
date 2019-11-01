#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "../Entity.h"
#include "../Game.h"

extern Game* game;

PlayerComponent::PlayerComponent(int maxLives)
{
    this->maxLives = maxLives;
}

void PlayerComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    if(!transform) { return; }
    origin = glm::vec2(transform->position.x, transform->position.y);
    currentLives = maxLives;
}

void PlayerComponent::Update(float deltaTime)
{

}

void PlayerComponent::Render()
{

}

void PlayerComponent::LoseLife()
{
    currentLives--;
    if(currentLives <= 0)
    {
        game->StopGame();
    }
    else
    {
        if(transform)
        {
            transform->position = origin;
        }
    }
}
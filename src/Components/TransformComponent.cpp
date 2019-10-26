#include "TransformComponent.h"
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../../lib/glm/glm.hpp"
#include "../Entity.h"
#include "KeyboardControlComponent.h"
#include "../Map.h"

TransformComponent::TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s, int r)
{
    componentName = "TransformComponent";
    position = glm::vec2(posX, posY);
    velocity = glm::vec2(velX, velY);
    width = w;
    height = h;
    scale = s;
    rotation = r;
}

void TransformComponent::Initialise() 
{

}
        
void TransformComponent::Update(float deltaTime)
{
    position += velocity * deltaTime;
    if(owner->HasComponent<KeyboardControlComponent>())
    {
        position.x = glm::clamp(position.x, 0.0f, static_cast<float>(Game::playAreaWidth -width));
        position.y = glm::clamp(position.y, 0.0f, static_cast<float>(Game::playAreaHeight - height));
    }
    
}

void TransformComponent::Render()
{
   
}
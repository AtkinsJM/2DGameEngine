#include "TransformComponent.h"
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../../lib/glm/glm.hpp"
// TODO: remove
#include "../Entity.h"
#include "KeyboardControlComponent.h"
#include "../Map.h"

TransformComponent::TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
{
    componentName = "TransformComponent";
    position = glm::vec2(posX, posY);
    velocity = glm::vec2(velX, velY);
    width = w;
    height = h;
    scale = s;
}

void TransformComponent::Initialise() 
{

}
        
void TransformComponent::Update(float deltaTime)
{
    position += velocity * deltaTime;
    if(owner->HasComponent<KeyboardControlComponent>())
    {
        // TODO: get map width and height for max clamp
        //position.x = Clamp(position.x, 0.0f, Game::map - width);
        //position.y = Clamp(position.y, 0.0f, 600.0f - height);
    }
    
}

void TransformComponent::Render()
{
   
}
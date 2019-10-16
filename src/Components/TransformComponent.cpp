#include "TransformComponent.h"
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../../lib/glm/glm.hpp"

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
}

void TransformComponent::Render()
{
   
}
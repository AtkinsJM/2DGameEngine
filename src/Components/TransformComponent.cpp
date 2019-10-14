#include "TransformComponent.h"
#include <SDL2/SDL.h>
#include "../Game.h"

TransformComponent::TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
{
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
    SDL_Rect transformRect{{(int)position.x, (int)position.y, width * scale, height * scale};
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(Game::renderer, &transformRect);
}
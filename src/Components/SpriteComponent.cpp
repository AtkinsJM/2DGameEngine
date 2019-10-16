#include "SpriteComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Game.h"
#include "TransformComponent.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Entity.h"

#include <iostream>

SpriteComponent::SpriteComponent(const char* filePath)
{
    componentName = "SpriteComponent";
    SetTexture(filePath);
}

void SpriteComponent::SetTexture(std::string textureID)
{
    std::cout << "Texture set with ID: " << textureID << std::endl;
    texture = Game::assetManager->GetTexture(textureID);
    std::cout << !texture << std::endl;
}

void SpriteComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = transform->width;
    sourceRect.h = transform->height;
}

void SpriteComponent::Update(float deltaTime)
{
    destinationRect.x = (int)transform->position.x;
    destinationRect.y = (int)transform->position.y;
    destinationRect.w = transform->width * transform->scale;
    destinationRect.h = transform->height * transform->scale;
}

void SpriteComponent::Render()
{
    TextureManager::DrawTexture(texture, sourceRect, destinationRect, spriteFlip);

}
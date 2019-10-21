#include "TileComponent.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "../AssetManager.h"

TileComponent::TileComponent(std::string textureID, int sourceRectX, int sourceRectY, int x, int y, int size, int scale)
{
    componentName = "TileComponent";
    this->texture = Game::assetManager->GetTexture(textureID);
    this->sourceRect.x = sourceRectX;
    this->sourceRect.y = sourceRectY;
    this->sourceRect.w = this->sourceRect.h = size;

    this->destinationRect.x = x;
    this->destinationRect.y = y;
    this->destinationRect.w = this->destinationRect.h = size * scale;

    this->position.x = x;
    this->position.y = y;
}

TileComponent::~TileComponent()
{
    SDL_DestroyTexture(texture);
}

void TileComponent::Update(float deltaTime)
{
    destinationRect.x = position.x - Game::camera.x;
    destinationRect.y = position.y - Game::camera.y;
}

void TileComponent::Render()
{
    TextureManager::DrawTexture(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
}
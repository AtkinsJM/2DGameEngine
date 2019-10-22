#include "LabelComponent.h"
#include "../FontManager.h"
#include "../Game.h"
#include "../AssetManager.h"
#include "../Entity.h"
#include "TransformComponent.h"

LabelComponent::LabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color color)
{
    componentName = "LabelComponent";
    this->position.x = x;
    this->position.y = y;
    SetLabelText(text, fontFamily, color);
}

void LabelComponent::SetLabelText(std::string text, std::string fontFamily, const SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void LabelComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    if(!transform) { return; }
    offsetX = position.x;
    offsetY = position.y;
    // TODO add ability to align to entity (enum?)
}

void LabelComponent::Update(float deltaTime)
{
    if(transform)
    {
        position.x = transform->position.x + offsetX - Game::camera.x;
        position.x -= (position.w - transform->width) / 2;
        position.y = transform->position.y + offsetY - Game::camera.y;
    }
}

void LabelComponent::Render()
{
    // TODO improve this logic
    if(Game::bShowObjectLabels || !transform)
    {
        FontManager::DrawFont(texture, position);
    }
}
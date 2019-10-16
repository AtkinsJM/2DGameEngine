#include "TextureManager.h"
#include "Game.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    std::cout << "File name: " << fileName << std::endl;
    SDL_Surface* surface = IMG_Load(fileName);
    std::cout << "Surface valid: " << surface << std::endl;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    std::cout << "Texture valid: " << texture << std::endl;
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::DrawTexture(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &sourceRect, &destinationRect, 0.0, NULL, flip);
}
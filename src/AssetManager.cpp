#include "AssetManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"

AssetManager::AssetManager(EntityManager* manager) : entityManager(manager)
{

}

void AssetManager::ClearData()
{
    textures.clear();
}

void AssetManager::AddTexture(std::string textureID, const char* filePath)
{
    SDL_Texture* texture = TextureManager::LoadTexture(filePath);
    textures.emplace(textureID, texture);
}

SDL_Texture* AssetManager::GetTexture(std::string textureID)
{
    return textures[textureID];
}
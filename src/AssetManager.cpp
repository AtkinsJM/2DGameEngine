#include "AssetManager.h"
#include "TextureManager.h"
#include "FontManager.h"

AssetManager::AssetManager(EntityManager* manager) : entityManager(manager)
{

}

void AssetManager::ClearData()
{
    textures.clear();
    fonts.clear();
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

void AssetManager::AddFont(std::string fontID, const char* filePath, int fontSize)
{
    TTF_Font* font = FontManager::LoadFont(filePath, fontSize);
    fonts.emplace(fontID, font);
}

TTF_Font* AssetManager::GetFont(std::string fontID)
{
    return fonts[fontID];
}
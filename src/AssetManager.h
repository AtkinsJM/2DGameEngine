#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <map>
//TODO: remove SDL includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class EntityManager;

class AssetManager
{
    public:
        AssetManager(EntityManager* manager);
        ~AssetManager();
        void ClearData();
        void AddTexture(std::string textureID, const char* filePath);
        SDL_Texture* GetTexture(std::string textureID);
        void AddFont(std::string fontID, const char* filePath, int fontSize);
        TTF_Font* GetFont(std::string fontID);

    private:
        EntityManager* entityManager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
};


#endif
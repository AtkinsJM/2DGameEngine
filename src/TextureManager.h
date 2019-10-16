#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static void DrawTexture(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip);

    private:
};

#endif
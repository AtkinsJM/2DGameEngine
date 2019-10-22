#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class FontManager
{
    public:
        static TTF_Font* LoadFont(const char* fileName, int fontSize);
        static void DrawFont(SDL_Texture* texture, SDL_Rect position);
    private:

};

#endif
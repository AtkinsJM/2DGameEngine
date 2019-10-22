#ifndef LABELCOMPONENT_H
#define LABELCOMPONENT_H

#include "../Component.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TransformComponent;

class LabelComponent: public Component
{
    public:
        LabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color color);
        void SetLabelText(std::string text, std::string fontFamily, const SDL_Color color);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
    private:
        SDL_Rect position;
        //std::string text;
        //std::string fontFamily;
        //SDL_Color color;
        SDL_Texture* texture;
        TransformComponent* transform;
        int offsetX;
        int offsetY;
};

#endif
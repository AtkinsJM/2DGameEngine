#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include "../Component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TransformComponent;

class SpriteComponent: public Component
{
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        SpriteComponent(const char* filePath);
        void SetTexture(std::string textureID);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;

    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destinationRect;
};

#endif
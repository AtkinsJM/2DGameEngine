#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "../Component.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TransformComponent;

class ColliderComponent : public Component
{
    public:
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRect;
        SDL_Rect destinationRect;
        TransformComponent* transform;

        ColliderComponent(std::string textureID, std::string colliderTag, int x, int y, int w, int h);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
    private:
        SDL_Texture* texture;
};

#endif
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "../Component.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Constants.h"

class TransformComponent;

class ColliderComponent : public Component
{
    public:
        //TODO: consider if I still need tags, or whether I can use collider types insted. Merge?
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRect;
        SDL_Rect destinationRect;
        TransformComponent* transform;
        std::string textureID;
        
        ColliderType colliderType;

        ColliderComponent(std::string colliderTag, ColliderType colliderType);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
    private:
        SDL_Texture* texture;
};

#endif
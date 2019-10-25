#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include "../Component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class TransformComponent;
class Animation;

class SpriteComponent: public Component
{
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        std::string textureID;
        bool bIsAnimated;
        int numFrames;
        int animSpeed;
        bool bIsFixed;
        bool bIsDirectional;
        SpriteComponent(std::string id);
        SpriteComponent(std::string id, int numFrames, int animSpeed, bool bIsDirectional, bool bIsFixed);
        void SetTexture(std::string textureID);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
        void PlayAnim(std::string animName);

    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destinationRect;
        
        std::map<std::string, Animation> anims;
        std::string currentAnimName;
        int animIndex = 0;
};

#endif
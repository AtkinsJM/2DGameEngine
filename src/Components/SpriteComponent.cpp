#include "SpriteComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Game.h"
#include "TransformComponent.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Entity.h"
#include "../Animation.h"

#include <iostream>

SpriteComponent::SpriteComponent(std::string id)
{
    componentName = "SpriteComponent";
    SetTexture(id);
    this->bIsAnimated = false;
    this->bIsFixed = false;
}

SpriteComponent::SpriteComponent(std::string id, int numFrames, int animSpeed, bool bIsDirectional, bool bIsFixed)
{
    componentName = "SpriteComponent";
    this->bIsAnimated = true;
    this->numFrames = numFrames;
    this->animSpeed = animSpeed;
    this->bIsFixed = bIsFixed;

    if(bIsDirectional)
    {
        Animation downAnim = Animation(0, numFrames, animSpeed);
        Animation rightAnim = Animation(1, numFrames, animSpeed);
        Animation leftAnim = Animation(2, numFrames, animSpeed);
        Animation upAnim = Animation(3, numFrames, animSpeed);
        
        anims.emplace("DownAnimation", downAnim);
        anims.emplace("RightAnimation", rightAnim);
        anims.emplace("LeftAnimation", leftAnim);
        anims.emplace("UpAnimation", upAnim);

        this->animIndex = 0;
        this->currentAnimName = "DownAnimation";
    }
    else
    {
        Animation singleAnim = Animation(0, numFrames, animSpeed);
        this->animIndex = 0;
        this->currentAnimName = "SingleAnimation";
        anims.emplace(this->currentAnimName, singleAnim);
    }
    PlayAnim(this->currentAnimName);

    SetTexture(id);
}

 void SpriteComponent::PlayAnim(std::string animName)
 {
     Animation currentAnim = anims[animName];
     numFrames = currentAnim.numFrames;
     animSpeed = currentAnim.animSpeed;
     animIndex = currentAnim.index;
     currentAnimName = animName;
 }

void SpriteComponent::SetTexture(std::string textureID)
{
    texture = Game::assetManager->GetTexture(textureID);
}

void SpriteComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = transform->width;
    sourceRect.h = transform->height;
}

void SpriteComponent::Update(float deltaTime)
{
    if(bIsAnimated)
    {
        // Get correct animation frame
        sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / animSpeed) % numFrames);
        sourceRect.y = animIndex * transform->height;
    }
    
    destinationRect.x = static_cast<int>(transform->position.x);
    destinationRect.y = static_cast<int>(transform->position.y);
    if(!bIsFixed)
    {
        destinationRect.x -= Game::camera.x;
        destinationRect.y -= Game::camera.y;
    }
    destinationRect.w = transform->width * transform->scale;
    destinationRect.h = transform->height * transform->scale;
}

void SpriteComponent::Render()
{
    TextureManager::DrawTexture(texture, sourceRect, destinationRect, spriteFlip);
}
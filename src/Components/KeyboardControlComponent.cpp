#include "KeyboardControlComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../Game.h"
#include "../Entity.h"

#include <iostream>
#include <string>

KeyboardControlComponent::KeyboardControlComponent()
{

}
KeyboardControlComponent::KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey)
{
    this->upKey = GetSDLKeyStringCode(upKey);
    this->rightKey = GetSDLKeyStringCode(rightKey);
    this->downKey = GetSDLKeyStringCode(downKey);
    this->leftKey = GetSDLKeyStringCode(leftKey);
    this->shootKey = GetSDLKeyStringCode(shootKey);

}

std::string KeyboardControlComponent::GetSDLKeyStringCode(std::string keyString)
{
    if(keyString == "up")
    {
        return "1073741906";
    }
    else if(keyString == "down")
    {
        return "1073741905";
    }
    else if(keyString == "right")
    {
        return "1073741903";
    }
    else if(keyString == "left")
    {
        return "1073741904";
    }
    else if(keyString == "space")
    {
        return "32";
    }
    else
    {
        return std::to_string(static_cast<int>(keyString[0]));
    }
}

void KeyboardControlComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    sprite = owner->GetComponent<SpriteComponent>();
    transform->velocity.x = 0;
    transform->velocity.y = 0;
}

void KeyboardControlComponent::Update(float deltaTime)
{
    if(Game::event.type == SDL_KEYDOWN)
    {
        std::string keyCode = std::to_string(Game::event.key.keysym.sym);
        if(keyCode == upKey)
        {
            transform->velocity.x = 0;
            transform->velocity.y = -100;
            sprite->PlayAnim("UpAnimation");
        }
        else if(keyCode == downKey)
        {
            transform->velocity.x = 0;
            transform->velocity.y = 100;
            sprite->PlayAnim("DownAnimation");
        }
        if(keyCode == rightKey)
        {
            transform->velocity.x = 100;
            transform->velocity.y = 0;
            sprite->PlayAnim("RightAnimation");
        }
        else if(keyCode == leftKey)
        {
            transform->velocity.x = -100;
            transform->velocity.y = 0;
            sprite->PlayAnim("LeftAnimation");
        }
        else if(keyCode == shootKey)
        {
            
        }
    }

    if(Game::event.type == SDL_KEYUP)
    {
        std::string keyCode = std::to_string(Game::event.key.keysym.sym);
        if(keyCode == upKey || keyCode == downKey)
        {
            transform->velocity.y = 0;
        }
        if(keyCode == rightKey || keyCode == leftKey)
        {
            transform->velocity.x = 0;
        }
    }
}

void KeyboardControlComponent::Render()
{

}
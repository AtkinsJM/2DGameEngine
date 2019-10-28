#include "KeyboardControlComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ProjectileEmitterComponent.h"
#include "../Game.h"
#include "../Entity.h"
#include "../../lib/glm/glm.hpp"
#include <iostream>
#include <string>


KeyboardControlComponent::KeyboardControlComponent()
{
    componentName = "KeyboardControlComponent";
}
KeyboardControlComponent::KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey)
{
    componentName = "KeyboardControlComponent";
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
    projectileEmitter = owner->GetComponent<ProjectileEmitterComponent>();
    if(!transform) { return; }
    transform->velocity.x = 0;
    transform->velocity.y = 0;
    directionVec = glm::vec2(0,1);
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
            directionVec = glm::vec2(0, -1);
        }
        else if(keyCode == downKey)
        {
            transform->velocity.x = 0;
            transform->velocity.y = 100;
            sprite->PlayAnim("DownAnimation");
            directionVec = glm::vec2(0, 1);
        }
        if(keyCode == rightKey)
        {
            transform->velocity.x = 100;
            transform->velocity.y = 0;
            sprite->PlayAnim("RightAnimation");
            directionVec = glm::vec2(1, 0);
        }
        else if(keyCode == leftKey)
        {
            transform->velocity.x = -100;
            transform->velocity.y = 0;
            sprite->PlayAnim("LeftAnimation");
            directionVec = glm::vec2(-1, 0);
        }
        else if(keyCode == shootKey)
        {
            if(projectileEmitter)
            {
                //std::cout << "Spawning projectile now..." << std::endl;
                std::cout << "(" << directionVec.x << ", " << directionVec.y << ")" << std::endl;
                glm::vec2 originVec = glm::vec2(1, 0);
                float cosAngle = glm::dot(directionVec, originVec);
                float angle = glm::acos(cosAngle) * (directionVec.x + directionVec.y);
                std::cout << "Cos angle: " << cosAngle << ", Angle: " << angle << std::endl;
                projectileEmitter->SpawnProjectile(angle);
            }
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
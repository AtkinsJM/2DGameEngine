#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Component.h"
#include "../../lib/glm/glm.hpp"
#include <string>

class TransformComponent;
class SpriteComponent;
class ProjectileEmitterComponent;

class KeyboardControlComponent: public Component
{
    public:
        std::string upKey;
        std::string downKey;
        std::string rightKey;
        std::string leftKey;
        std::string shootKey;
        TransformComponent* transform;
        SpriteComponent* sprite;
        ProjectileEmitterComponent* projectileEmitter;

        KeyboardControlComponent();
        KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey);

        std::string GetSDLKeyStringCode(std::string keyString);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
    private:
        glm::vec2 directionVec;

};

#endif
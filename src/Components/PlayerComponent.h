#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "../Component.h"
#include "../../lib/glm/glm.hpp"

class TransformComponent;

class PlayerComponent: public Component
{
    public:
        PlayerComponent(int maxLives);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
        int CurrentLives() { return currentLives; }
        void LoseLife();
    private:
        glm::vec2 origin;
        int currentLives;
        int maxLives;
        TransformComponent* transform;
};

#endif
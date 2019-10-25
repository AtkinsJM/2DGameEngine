#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include "../Component.h"
#include "../../lib/glm/glm.hpp"

class TransformComponent;

class ProjectileComponent: public Component
{
    public:
        int speed;
        int range;
        float angleRad;
        ProjectileComponent(int speed, int range, float angleRad);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
    private:
        TransformComponent* transform;
        glm::vec2 origin;
        
};

#endif
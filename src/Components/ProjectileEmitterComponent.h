#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../Component.h"
#include "../../lib/glm/glm.hpp"

class TransformComponent;

class ProjectileEmitterComponent: public Component
{
    public:
        ProjectileEmitterComponent(int speed, int range, int angleDeg, float spawnDelay, bool bIsLooping);
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;
        Entity& SpawnProjectile();
    private:
        TransformComponent* transform;
        glm::vec2 origin;
        int speed;
        int range;
        float angleRad;
        bool bIsLooping;
        float lastSpawnTime;
        float spawnDelay;
};

#endif
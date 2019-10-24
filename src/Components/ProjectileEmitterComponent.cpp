#include "ProjectileEmitterComponent.h"
#include "../Entity.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "../EntityManager.h"
#include "ProjectileComponent.h"
#include <SDL2/SDL.h>
#include "../Constants.h"

extern EntityManager entityManager;

ProjectileEmitterComponent::ProjectileEmitterComponent(int speed, int range, int angleDeg, float spawnDelay, bool bIsLooping)
{
    componentName = "ProjectileEmitterComponent";
    this->speed = speed;
    this->range = range;
    this->bIsLooping = bIsLooping;
    this->angleRad = glm::radians(static_cast<float>(angleDeg));
    this->spawnDelay = spawnDelay;
}

void ProjectileEmitterComponent::Initialise()
{
    transform = owner->GetComponent<TransformComponent>();
    if(!transform) { return; }
    lastSpawnTime = 0.0f;
}

void ProjectileEmitterComponent::Update(float deltaTime)
{
    // If time since last spawn greater than spawn delay
    if((SDL_GetTicks() - lastSpawnTime) / 1000.0f > spawnDelay)
    {
        // Spawn a new projectile
        SpawnProjectile();
        lastSpawnTime = SDL_GetTicks();
    }
}

void ProjectileEmitterComponent::Render()
{

}

Entity& ProjectileEmitterComponent::SpawnProjectile()
{
    Entity& projectile = entityManager.AddEntity("projectile", PROJECTILE_LAYER);
    projectile.AddComponent<TransformComponent>(transform->position.x + 16, transform->position.y + 16, 0, 0, 4, 4, 1);
    projectile.AddComponent<SpriteComponent>("projectile-texture");
    projectile.AddComponent<ColliderComponent>("collision-texture", "Projectile", ColliderType::PROJECTILE_ENEMY, transform->position.x + 16, transform->position.y + 16, 4, 4);
    projectile.AddComponent<ProjectileComponent>(speed, range, angleRad);
}
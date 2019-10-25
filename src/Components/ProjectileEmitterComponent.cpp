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

ProjectileEmitterComponent::ProjectileEmitterComponent(Entity* projectilePrefab, int speed, int range, int angleDeg, float spawnDelay, bool bIsLooping)
{
    componentName = "ProjectileEmitterComponent";
    this->projectilePrefab = projectilePrefab;
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
    Entity& projectile = entityManager.Instantiate(projectilePrefab, transform->position.x + transform->width/2, transform->position.y + transform->height/2);

    /*
    Entity& projectile = entityManager.AddEntity(projectilePrefab->EntityName(), projectilePrefab->layer);
    projectile.AddComponent<TransformComponent>(transform->position.x + transform->width/2, transform->position.y + transform->height/2, 0, 0, projectilePrefab->GetComponent<TransformComponent>()->width, projectilePrefab->GetComponent<TransformComponent>()->height, 1);
    projectile.AddComponent<SpriteComponent>("projectile-texture");
    projectile.AddComponent<ColliderComponent>("collision-texture", "Projectile", ColliderType::PROJECTILE_ENEMY);
    projectile.AddComponent<ProjectileComponent>(speed, range, angleRad);
    */
}
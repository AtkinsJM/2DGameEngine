#include "ProjectileEmitterComponent.h"
#include "../Entity.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "KeyboardControlComponent.h"
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
    this->bCanFire = true;
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
        bCanFire = true;
        // Spawn a new projectile
        if(!owner->GetComponent<KeyboardControlComponent>())
        {
            SpawnProjectile(angleRad);  
        }
    }
}

void ProjectileEmitterComponent::Render()
{

}

void ProjectileEmitterComponent::SpawnProjectile(float angle)
{
    if(!bCanFire) { return; }
    int projectilePosX = transform->position.x + (transform->width / 2) - (projectilePrefab->GetComponent<TransformComponent>()->width / 2);
    int projectilePosY = transform->position.y + (transform->height / 2) - (projectilePrefab->GetComponent<TransformComponent>()->width / 2);
    Entity& projectile = entityManager.Instantiate(projectilePrefab, projectilePosX, projectilePosY);
    projectile.GetComponent<ProjectileComponent>()->angleRad = angle;
    projectile.InitialiseComponents();
    bCanFire = false;
    lastSpawnTime = SDL_GetTicks();
}
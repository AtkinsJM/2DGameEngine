#include "Collision.h"

// TODO improve/add another method to check collision types and whether they should be colliding or not
bool Collision::CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    return (rectA.x + rectA.w >= rectB.x &&
            rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y &&
            rectB.y + rectB.h >= rectA.y);
}

bool Collision::CheckCollisionTypes(ColliderType typeA, ColliderType typeB)
{
    if(typeA == ColliderType::PLAYER && typeB == ColliderType::ENEMY ||
        typeA == ColliderType::ENEMY && typeB == ColliderType::PLAYER ||
        typeA == ColliderType::PLAYER && typeB == ColliderType::PROJECTILE_ENEMY ||
        typeA == ColliderType::PROJECTILE_ENEMY && typeB == ColliderType::PLAYER ||
        typeA == ColliderType::ENEMY && typeB == ColliderType::PROJECTILE_PLAYER ||
        typeA == ColliderType::PROJECTILE_PLAYER && typeB == ColliderType::ENEMY)
    {
        return true;
    }
    return false;
}
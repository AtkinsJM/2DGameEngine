#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include "Constants.h"

class Collision
{
    public:
        static bool CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
        static bool CheckCollisionTypes(ColliderType typeA, ColliderType typeB);
    private:

};

#endif
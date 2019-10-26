#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../../lib/glm/glm.hpp"
#include "../Component.h"

class TransformComponent: public Component
{
    public:
        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s, int r);
       
        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
        int rotation;
        
        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;

        template<typename T>
        const T& Clamp(T num, T min, T max)
        {
            return num <= min ? min : num >= max ? max : num;
        }

    private:

};

#endif
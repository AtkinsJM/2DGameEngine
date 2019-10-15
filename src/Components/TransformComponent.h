#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../Component.h"

class TransformComponent: public Component
{
    public:
        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s);

        

        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
        

        void Initialise() override;
        void Update(float deltaTime) override;
        void Render() override;

    private:

};

#endif
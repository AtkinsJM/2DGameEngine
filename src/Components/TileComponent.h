#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include  "../../lib/glm/glm.hpp"
#include <string>
#include "../Component.h"


class TileComponent: public Component
{
    public:
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destinationRect;
        glm::vec2 position;

        TileComponent(std::string textureID, int sourceRectX, int sourceRectY, int x, int y, int size, int scale);
        ~TileComponent();

        void Update(float deltaTime) override;
        void Render() override;
    private:
};

#endif
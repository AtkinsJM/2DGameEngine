#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
    public:
        Game();
        ~Game();
        bool IsRunning() const { return isRunning; };
        void Initialise(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int ticksLastFrame = 0;
};

#endif
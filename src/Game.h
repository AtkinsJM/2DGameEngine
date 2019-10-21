#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

class AssetManager;

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
        void LoadLevel(int levelNumber);
        void HandleCameraMovement();
        void CheckCollisions();
        static SDL_Renderer* renderer;
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
    private:
        bool isRunning;
        SDL_Window* window;
        int ticksLastFrame = 0;
};

#endif
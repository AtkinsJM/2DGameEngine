#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../lib/lua/sol.hpp"
#include "../lib/lua/lua.hpp"

class AssetManager;

class Game
{
    public:
        Game();
        ~Game();
        bool IsRunning() const { return bIsRunning; };
        void Initialise(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
        void LoadLevel(int levelNumber);
        void HandleCameraMovement();
        static SDL_Renderer* renderer;
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        static bool bShowColliders;
        static bool bShowObjectLabels;
        static int playAreaWidth;
        static int playAreaHeight;

    private:
        bool bIsRunning;
        SDL_Window* window;
        int ticksLastFrame = 0;
};

#endif
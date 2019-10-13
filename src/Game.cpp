#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVelocity = glm::vec2(80.0f, 60.0f);

Game::Game()
{
    this->isRunning = false;
}

Game::~Game()
{

}

void Game::Initialise(int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initialising SDL" << std::endl;
        return;
    }
    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(!window)
    {
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer)
    {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return;
    }
    isRunning = true;
    return;
}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            break;
        default:
            break;
    }
}

void Game::Update()
{
    // Wait for target FPS
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    // Calculate the time since last frame in seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    // Clamp deltaTime
    deltaTime = (deltaTime > MAX_DELTA_TIME) ? MAX_DELTA_TIME : deltaTime;
    // Set time of current frame
    ticksLastFrame = SDL_GetTicks();
    
    // Update projectile position
    projectilePos += projectileVelocity * deltaTime;

}

void Game::Render()
{
    // Set the background colour
    SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
    // Clear the back buffer
    SDL_RenderClear(renderer);

    SDL_Rect projectile{(int)projectilePos.x, (int)projectilePos.y, 10, 10};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    // Swap front and back buffers
    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
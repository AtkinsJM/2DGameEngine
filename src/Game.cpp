#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"
#include "EntityManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Entity.h"
#include "AssetManager.h"
#include <string>


EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer* Game::renderer;

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

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber)
{
    //Add new assets to AssetManager
    std::string textureFilePath = "assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());
    //Add new entities and their components to EntityManager



    auto& newEntity = entityManager.AddEntity("Projectile");
    newEntity.AddComponent<TransformComponent>(0, 0, 80, 60, 20, 20, 1);

    auto& newEntity2 = entityManager.AddEntity("Projectile_2");
    newEntity2.AddComponent<TransformComponent>(200, 0, 0, 100, 10, 10, 1);

    auto& newEntity3 = entityManager.AddEntity("tank");
    newEntity3.AddComponent<TransformComponent>(0, 300, 100, 0, 15, 15, 1);
    newEntity3.AddComponent<SpriteComponent>("tank-image");

     auto& newEntity4 = entityManager.AddEntity("Projectile_4");
    newEntity4.AddComponent<TransformComponent>(0, 600, 80, -60, 20, 20, 1);

    entityManager.ListAllEntities();
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
 
    entityManager.Update(deltaTime);
}

void Game::Render()
{
    // Set the background colour
    SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
    // Clear the back buffer
    SDL_RenderClear(renderer);

    if(!entityManager.HasEntities()) { return; }
    entityManager.Render();

    // Swap front and back buffers
    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
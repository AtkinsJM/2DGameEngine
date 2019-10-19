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
#include <time.h>


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
    srand(time(NULL));

    assetManager->AddTexture("tank-image", std::string("assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("helicopter-image", std::string("assets/images/chopper-spritesheet.png").c_str());
    //Add new entities and their components to EntityManager

    auto& tankEntity = entityManager.AddEntity("tank_1");
    tankEntity.AddComponent<TransformComponent>(0, 100, rand() % 100 + 51, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");


    auto& helicopterEntity = entityManager.AddEntity("helicopter_1");
    helicopterEntity.AddComponent<TransformComponent>(200, 200, 0, 100, 32, 32, 1);
    helicopterEntity.AddComponent<SpriteComponent>("helicopter-image", 2, 90, true, false);
/*
    auto& newEntity2 = entityManager.AddEntity("tank_2");
    newEntity2.AddComponent<TransformComponent>(0, 200, rand() % 100 + 51, 0, 32, 32, 1);
    //newEntity2.AddComponent<SpriteComponent>("tank-image");
    std::cout << newEntity2.HasComponent<SpriteComponent>() << std::endl;

    auto& newEntity3 = entityManager.AddEntity("tank_3");
    newEntity3.AddComponent<TransformComponent>(0, 300, rand() % 100 + 51, 0, 32, 32, 1);
    newEntity3.AddComponent<SpriteComponent>("tank-image");

    auto& newEntity4 = entityManager.AddEntity("tank_4");
    newEntity4.AddComponent<TransformComponent>(0, 400, rand() % 100 + 51, 0, 32, 32, 1);
    newEntity4.AddComponent<SpriteComponent>("tank-image");

    auto& newEntity5 = entityManager.AddEntity("tank_5");
    newEntity5.AddComponent<TransformComponent>(0, 500, rand() % 100 + 51, 0, 32, 32, 1);
    newEntity5.AddComponent<SpriteComponent>("tank-image");
*/
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
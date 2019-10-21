#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"
#include "EntityManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Entity.h"
#include "AssetManager.h"
#include <string>
#include <time.h>
#include "Map.h"
#include <vector>

EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
bool Game::bShowColliders = false;
Map* map;
Entity* player;

Game::Game()
{
    this->bIsRunning = false;
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

    bIsRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber)
{
    srand(time(NULL));

    assetManager->AddTexture("tank-image", std::string("assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("helicopter-image", std::string("assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tilemap", std::string("assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("collision-image", std::string("assets/images/collision-texture.png").c_str());
    
    map = new Map("jungle-tilemap", 2, 32);
    map->LoadMap(std::string("assets/tilemaps/jungle.map").c_str(), 25, 20);

    //Add new entities and their components to EntityManager

    Entity& tankEntity = entityManager.AddEntity("tank_1", LayerType::ENEMY_LAYER);
    tankEntity.AddComponent<TransformComponent>(0, 100, rand() % 100 + 51, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");
    tankEntity.AddComponent<ColliderComponent>("collision-image", "Enemy", 0, 100, 32, 32);

    //Entity& helicopterEntity = entityManager.AddEntity("helicopter_1", LayerType::PLAYER_LAYER);
    Entity& helicopterEntity = entityManager.AddEntity("helicopter_1", LayerType::PLAYER_LAYER);
    helicopterEntity.AddComponent<TransformComponent>(200, 200, 0, 100, 32, 32, 1);
    helicopterEntity.AddComponent<SpriteComponent>("helicopter-image", 2, 90, true, false);
    helicopterEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    helicopterEntity.AddComponent<ColliderComponent>("collision-image", "Player", 200, 200, 32, 32);
    player = &helicopterEntity;

    Entity& radarEntity = entityManager.AddEntity("radar", LayerType::UI_LAYER);
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    //entityManager.ListAllEntities();
}

void Game::ProcessInput()
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            bIsRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                bIsRunning = false;
            }
            else if (event.key.keysym.sym == SDLK_c)
            {   
                // Toggle collider bounding boxes
                bShowColliders = !bShowColliders;
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

    HandleCameraMovement();
    CheckCollisions();
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

void Game::HandleCameraMovement()
{
    if(!player) { return; }
    TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);
    // TODO: sort for map scale
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions()
{
    // Get tags of all colliders in collision with entity
    std::vector<std::string> colliderTags = entityManager.GetEntityCollisions(player);
    for(auto tag : colliderTags)
    {
        std::cout << tag << std::endl;
    }
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
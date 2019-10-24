#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"
#include "EntityManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/LabelComponent.h"
#include "Components/ProjectileEmitterComponent.h"
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
bool Game::bShowObjectLabels = false;
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
    if(TTF_Init() != 0)
    {
        std::cerr << "Error initialising SDL TTF" << std::endl;
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
    assetManager->AddTexture("projectile-image", std::string("assets/images/bullet-enemy.png").c_str());

    assetManager->AddFont("charriot-font", std::string("assets/fonts/charriot.ttf").c_str(), 16);
    assetManager->AddFont("charriot-font-small", std::string("assets/fonts/charriot.ttf").c_str(), 12);
    assetManager->AddFont("arial-font", std::string("assets/fonts/arial.ttf").c_str(), 14);
    
    map = new Map("jungle-tilemap", 2, 32);
    map->LoadMap(std::string("assets/tilemaps/jungle.map").c_str(), 25, 20);

    //Add new entities and their components to EntityManager

    Entity& tankEntity = entityManager.AddEntity("tank_1", ENEMY_LAYER);
    tankEntity.AddComponent<TransformComponent>(0, 100, 50, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");
    tankEntity.AddComponent<ColliderComponent>("collision-image", "Enemy", ColliderType::ENEMY, 0, 100, 32, 32);
    tankEntity.AddComponent<LabelComponent>(0, 40, "Enemy", "charriot-font-small", RED_COLOR);
    tankEntity.AddComponent<ProjectileEmitterComponent>(125, 375, 0, 2.0f, true);
    

    Entity& helicopterEntity = entityManager.AddEntity("helicopter_1", PLAYER_LAYER);
    helicopterEntity.AddComponent<TransformComponent>(200, 200, 0, 100, 32, 32, 1);
    helicopterEntity.AddComponent<SpriteComponent>("helicopter-image", 2, 90, true, false);
    helicopterEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    helicopterEntity.AddComponent<ColliderComponent>("collision-image", "Player", ColliderType::PLAYER, 200, 200, 32, 32);
    helicopterEntity.AddComponent<LabelComponent>(0, 40, "Player", "charriot-font-small", GREEN_COLOR);
    player = &helicopterEntity;

    Entity& radarEntity = entityManager.AddEntity("radar", UI_LAYER);
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity& labelLevelName = entityManager.AddEntity("LabelLevelName", UI_LAYER);
    labelLevelName.AddComponent<LabelComponent>(10, 10, "Level 1", "charriot-font", WHITE_COLOR);
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
            else if (event.key.keysym.sym == SDLK_TAB)
            {
                bShowObjectLabels = true;
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_TAB)
            {
                bShowObjectLabels = false;
            }
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

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
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
#include "Components/ProjectileComponent.h"
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
Entity* labelPlayerPosition;
int Game::playAreaWidth = WINDOW_WIDTH;
int Game::playAreaHeight = WINDOW_HEIGHT;

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

    LoadLevel(1);

    bIsRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber)
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    
    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("assets/scripts/" + levelName + ".lua");

    /*****************************************************/
    /* LOAD ASSETS FROM LUA CONFIG FILE                  */
    /*****************************************************/
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];

    unsigned int assetIndex = 0;
    while(true)
    {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if(existsAssetIndexNode == sol::nullopt) { break; }

        sol::table asset = levelAssets[assetIndex];
        std::string assetType = asset["type"];
        std::string assetID = asset["id"];
        std::string assetFile = asset["file"];

        if(assetType == "texture")
        {
            assetManager->AddTexture(assetID, assetFile.c_str());
        }
        else if (assetType == "font")
        {
            int assetFontSize = asset["fontSize"];
            assetManager->AddFont(assetID, assetFile.c_str(), assetFontSize);
        }
        assetIndex++;
    }

    /*****************************************************/
    /* LOAD MAP AND TILE DATA FROM LUA CONFIG FILE       */
    /*****************************************************/
    sol::table levelMap = levelData["map"];
    std::string mapTextureID = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];
    int mapScale = levelMap["scale"];
    int tileSize = levelMap["tileSize"];
    int mapSizeX = levelMap["mapSizeX"];
    int mapSizeY = levelMap["mapSizeY"];

    playAreaWidth = tileSize * mapScale * mapSizeX;
    playAreaHeight = tileSize * mapScale * mapSizeY;

    std::cout << "Width: " << playAreaWidth << std::endl;
    std::cout << "Height: " << playAreaHeight << std::endl;

    map = new Map(mapTextureID, mapScale, tileSize);
    map->LoadMap(mapFile.c_str(), mapSizeX, mapSizeY);

    /*****************************************************/
    /* LOAD ENTITIES AND COMPONENTS FROM LUA CONFIG FILE */
    /*****************************************************/
    sol::table levelEntities = levelData["entities"];

    unsigned int entityIndex = 0;
    while(true)
    {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
        if(existsEntityIndexNode == sol::nullopt) { break; }

        sol::table entity = levelEntities[entityIndex];
        std::string entityName = entity["name"];
        
        LayerType entityLayerType = static_cast<LayerType>(entity["layer"]);

        Entity& newEntity = entityManager.AddEntity(entityName, entityLayerType);
         
        
        sol::table entityComponents = entity["components"];
        
        sol::optional<sol::table> existsTransformComponent = entityComponents["transform"];
        if(existsTransformComponent != sol::nullopt)
        {
            sol::table transform = entityComponents["transform"];
            int posX = transform["position"]["x"];
            int posY = transform["position"]["y"];
            int velX = transform["velocity"]["x"];
            int velY = transform["velocity"]["y"];
            int width = transform["width"];
            int height = transform["height"];
            int scale = transform["scale"];
            int rotation = transform["rotation"];
            newEntity.AddComponent<TransformComponent>(posX, posY, velX, velY, width, height, scale, rotation);
        }
        
        sol::optional<sol::table> existsSpriteComponent = entityComponents["sprite"];
        if(existsSpriteComponent != sol::nullopt)
        {
            sol::table sprite = entityComponents["sprite"];
            std::string textureAssetId = sprite["textureAssetId"];
            bool bAnimated = sprite["animated"];
            if(bAnimated)
            {
                int frameCount = sprite["frameCount"];
                int animSpeed = sprite["animationSpeed"];
                bool bIsDirectional = sprite["directional"];
                bool bIsFixed = sprite["fixed"];
                newEntity.AddComponent<SpriteComponent>(textureAssetId, frameCount, animSpeed, bIsDirectional, bIsFixed);
            }
            else
            {
                newEntity.AddComponent<SpriteComponent>(textureAssetId);
            }
        }
        
        sol::optional<sol::table> existsColliderComponent = entityComponents["collider"];
        if(existsColliderComponent != sol::nullopt)
        {
            sol::table collider = entityComponents["collider"];
            std::string tag = collider["tag"];
            int colliderType = collider["collisionType"];
            newEntity.AddComponent<ColliderComponent>(tag, static_cast<ColliderType>(colliderType));
        }
            
        sol::optional<sol::table> existsInputComponent = entityComponents["input"];
        if(existsInputComponent != sol::nullopt)
        {
            sol::table input = entityComponents["input"];
           
            sol::optional<sol::table> existsKeyboardComponent = input["keyboard"];
            if(existsKeyboardComponent != sol::nullopt)
            if(input["keyboard"])
            {
                sol::table keyboard = input["keyboard"];
                std::string up = keyboard["up"];
                std::string left = keyboard["left"];
                std::string right = keyboard["right"];
                std::string down = keyboard["down"];
                std::string shoot = keyboard["shoot"];
                newEntity.AddComponent<KeyboardControlComponent>(up, right, down, left, shoot);
            }
        }
        
        sol::optional<sol::table> existsLabelComponent = entityComponents["label"];
        if(existsLabelComponent != sol::nullopt)
        {
            sol::table label = entityComponents["label"];
            int posX = label["position"]["x"];
            int posY = label["position"]["y"];
            std::string text = label["text"];
            std::string fontId = label["fontId"];
            SDL_Color color = {label["color"]["r"], label["color"]["g"], label["color"]["b"], label["color"]["a"]};
            newEntity.AddComponent<LabelComponent>(posX, posY, text, fontId, color);
        }

        sol::optional<sol::table> existsProjectileEmitterComponent = entityComponents["projectileEmitter"];
        if(existsProjectileEmitterComponent != sol::nullopt)
        {
            sol::table projectileEmitter = entityComponents["projectileEmitter"];
            int speed = projectileEmitter["speed"];
            int range = projectileEmitter["range"];
            // TODO have angle as a property of the projectile, not the emitter
            int angle = projectileEmitter["angle"];
            float spawnDelay = projectileEmitter["spawnDelay"];
            bool bIsLooping = projectileEmitter["isLooping"];

            std::string projectileName = projectileEmitter["projectile"]["name"];
            LayerType projectileLayerType = static_cast<LayerType>(projectileEmitter["projectile"]["layer"]);
            std::string textureAssetId = projectileEmitter["projectile"]["textureAssetId"];
            int projectileSize = projectileEmitter["projectile"]["size"];
            int projectileScale = projectileEmitter["projectile"]["scale"];
            std::string projectileColliderTag = projectileEmitter["projectile"]["colliderTag"];
            ColliderType projectileColliderType = static_cast<ColliderType>(projectileEmitter["projectile"]["colliderType"]);

            Entity* projectilePrefab = new Entity(entityManager, projectileName, projectileLayerType);
            projectilePrefab->AddComponent<TransformComponent>(0, 0, 0, 0, projectileSize, projectileSize, projectileScale, angle);
            projectilePrefab->AddComponent<SpriteComponent>(textureAssetId);
            projectilePrefab->AddComponent<ColliderComponent>(projectileColliderTag, projectileColliderType);
            float angleRad = glm::radians(static_cast<float>(angle));
            projectilePrefab->AddComponent<ProjectileComponent>(speed, range, angleRad);

            newEntity.AddComponent<ProjectileEmitterComponent>(projectilePrefab, speed, range, angle, spawnDelay, bIsLooping);

        }   
        newEntity.InitialiseComponents();     
        entityIndex++;
    }

    player = entityManager.GetEntityByName("player");
    labelPlayerPosition = entityManager.GetEntityByName("labelPlayerPosition");

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
    if(labelPlayerPosition && player)
    {
        glm::vec2 playerPosition = player->GetComponent<TransformComponent>()->position;
        std::string text = "Position: (" + std::to_string(static_cast<int>(playerPosition.x)) + ", " + std::to_string(static_cast<int>(playerPosition.y)) + ")";
        labelPlayerPosition->GetComponent<LabelComponent>()->SetLabelText(text);
    }
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

    camera.x = glm::clamp(camera.x, 0, playAreaWidth - camera.w);
    camera.y = glm::clamp(camera.y, 0, playAreaHeight - camera.h);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
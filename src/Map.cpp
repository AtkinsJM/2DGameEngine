#include "Map.h"
#include "Game.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"
#include "Constants.h"

#include <fstream>
#include <iostream>

extern EntityManager entityManager;

Map:: Map(std::string textureID, int scale, int tileSize)
{
    this->textureID = textureID;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int sizeX, int sizeY)
{
    std::fstream mapFile;
    mapFile.open(filePath);

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            AddTile(sourceRectX, sourceRectY, x * scale * tileSize, y * scale * tileSize);
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y)
{
    Entity& newTile = entityManager.AddEntity("Tile", LayerType::TILEMAP_LAYER);
    newTile.AddComponent<TileComponent>(textureID, sourceRectX, sourceRectY, x, y, tileSize, scale);
    //std::cout << "About to initialise tile!" << std::endl;
    newTile.InitialiseComponents();
}
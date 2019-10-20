#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{
    public:
        Map(std::string textureID, int scale, int tileSize);
        ~Map();
        void LoadMap(std::string filePath, int sizeX, int sizeY);
        void AddTile(int sourceRectX, int sourceRectY, int x, int y);
    private:
        std::string textureID;
        int scale;
        int tileSize;
};

#endif
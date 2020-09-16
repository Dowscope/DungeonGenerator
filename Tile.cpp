#include "Tile.h"


Tile::Tile(int x, int y):
    _x(x), _y(y)
{
    
}

void Tile::resetWalls(const bool allWalls){
    for (int i = 0; i < 4; i++)
    {
        _walls[i] = allWalls;
    }
}

void Tile::setWallAt(int location, bool isWall){
    _walls[location] = isWall;
}
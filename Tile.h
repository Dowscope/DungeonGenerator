/************************************************************
 * Tile.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef TILE_H
#define Tile_H

class Tile{
private:
    int _x, _y;
    int _walls[4] = {true, true, true, true}; // Up Right DOwn Left
    bool _visited = false;
    bool _roomTile = false;
public:
    bool isCurrent = false;
    Tile(int x, int y);
    ~Tile();
    bool isWallAt(int location) {return _walls[location];}
    void resetWalls(bool allWalls);
    int getX() {return _x;} 
    int getY() {return _y;}
    int isVisited() {return _visited;}
    int isRoomTile() {return _roomTile;}
    void makeRoomTile() {_roomTile = true;}
    void Visited() {_visited = true;}
    void setWallAt(int location, bool isWall);
};

Tile::Tile(int x, int y):
    _x(x), _y(y)
{
    
}

void Tile::resetWalls(bool allWalls){
    for (int i = 0; i < 4; i++)
    {
        _walls[i] = allWalls;
    }
}

void Tile::setWallAt(int location, bool isWall){
    _walls[location] = isWall;
}

#endif
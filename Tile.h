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
    bool isWallAt(const int location) {return _walls[location];}
    void resetWalls(const bool allWalls);
    int getX() {return _x;} 
    int getY() {return _y;}
    int isVisited() {return _visited;}
    int isRoomTile() {return _roomTile;}
    void makeRoomTile() {_roomTile = true;}
    void Visited() {_visited = true;}
    void setWallAt(const int location, const bool isWall);
};


#endif
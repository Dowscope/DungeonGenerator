/************************************************************
 * World.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Room.h"
#include "Tile.h"

class World{
private:
    const int MAX_ROOMS = 10;
    const int MIN_ROOM_SIZE = 3;
    const int MAX_ROOM_SIZE = 10;
    int _width, _height;
    std::vector<Room*> _rooms;
    std::vector<Tile*> _tiles;
    std::vector<Tile*> _mazeStack;
    void _initializeTiles();
    void _generateMap();
    void _walkMaze();
    Tile* _checkNeighbours(Tile *nb);
    void _removeWalls(Tile* t, Tile* nb);
    bool _checkForOverlap(Room *r);
public:
    World(int aWidth, int aHeight);
    ~World();

    Tile* getTileAt(const int x, const int y);

    std::vector<Room*> getRooms() {return _rooms;}
    int getWorldWidth() {return _width;}
    int getWorldHeight() {return _height;}
};

#endif
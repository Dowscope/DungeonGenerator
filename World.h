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
    const int MAX_ROOMS = 20;
    const int MIN_ROOM_SIZE = 3;
    const int MAX_ROOM_SIZE = 10;
    int _width, _height;
    std::vector<Room*> _rooms;
    std::vector<Tile*> _tiles;
    void _initializeTiles();
    void _generateMap();
    bool _checkForOverlap(Room *r);
public:
    World(int aWidth, int aHeight);
    ~World();

    Tile* getTileAt(int x, int y);

    std::vector<Room*> getRooms() {return _rooms;}
    int getWorldWidth() {return _width;}
    int getWorldHeight() {return _height;}
};

World::World(int aWidth, int aHeight):
    _width(aWidth), _height(aHeight)
{
    _initializeTiles();
    _generateMap();
}

void World::_initializeTiles(){
    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            Tile *t = new Tile(x, y);
            _tiles.push_back(t);
        }
        
    }
    
    std::cout << "Total tiles initialized: " << _tiles.size() << std::endl;
}

void World::_generateMap(){
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        int x = rand() % _width;
        int y = rand() % _height;
        int w = MIN_ROOM_SIZE + rand() % MAX_ROOM_SIZE;
        int h = MIN_ROOM_SIZE + rand() % MAX_ROOM_SIZE;

        if (x >= _width - w) { x = x - w; }
        if (y >= _height - h) { y = y - h; }

        Room *r = new Room(x, y, w, h);
        if ( !_checkForOverlap(r)){
            _rooms.push_back(r);

            for (int row = y; row < y + h; row++)
            {
                for (int col = x; col < x + w; col++)
                {
                    Tile *t = getTileAt(col, row);
                    t->resetWalls(false);

                    if (row == 0){ t->setWallAt(0, true); }
                    if (col == 0){ t->setWallAt(3, true); }
                    if (row == y + h - 1){ t->setWallAt(2, true);}
                    if (col == x + w - 1){ t->setWallAt(1, true);}

                    t->Visited();
                    t->makeRoomTile();
                }
            }
        }
    }  

    // Make Maze
    // Start at (0,0) for time being.
    
     
}

bool World::_checkForOverlap(Room *r){

    if (_rooms.empty() == true){
        return false;
    }
    bool checker = false;

    for (int i = 0; i < _rooms.size(); i++){
        Room *room = _rooms[i];
        if (    r->getX() + r->getW() < room->getX() || 
                r->getY() + r->getH() < room->getY() || 
                r->getX() > room->getX() + room->getW() ||
                r->getY() > room->getY() + room->getH() )
        {

        }
        else {
            checker = true;
        }
    }

    return checker;
}

Tile* World::getTileAt(int x, int y){
    for (int i = 0; i < _tiles.size(); i++)
    {
        Tile *t = _tiles[i];
        if (t->getX() == x && t->getY() == y){
            return t;
        }
    }
    
    return nullptr;
}

#endif
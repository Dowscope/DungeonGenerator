/************************************************************
 * World.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Room.h"

class World{
private:
    const int MAX_ROOMS = 20;
    const int MIN_ROOM_SIZE = 3;
    const int MAX_ROOM_SIZE = 10;
    int _width, _height;
    std::vector<Room*> _rooms;
    void _generateMap();
    bool _checkForOverlap(Room *r);
public:
    World(int aWidth, int aHeight);
    ~World();

    std::vector<Room*> getRooms() {return _rooms;}
    int getWorldWidth() {return _width;}
    int getWorldHeight() {return _height;}
};

World::World(int aWidth, int aHeight):
    _width(aWidth), _height(aHeight)
{
    _generateMap();
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
        }
    }   
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

#endif
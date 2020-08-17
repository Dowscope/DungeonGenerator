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
    std::vector<Room> _rooms;
public:
    World();
    ~World();
};

World::World(){

}

#endif
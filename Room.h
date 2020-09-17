/************************************************************
 * Room.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <random>
#include "Vector2D.h"

struct Room{
    int x, y, w, h;
    Vector2D doorLocation;
    Room(int x, int y, int w, int h);
    ~Room();

    void generateDoor();
};

#endif
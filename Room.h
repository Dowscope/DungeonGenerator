/************************************************************
 * Room.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <random>

class Room{
private:
    int _x, _y, _w, _h;
    void _generateDoors(const int doors);
public:
    Room(int x, int y, int w, int h);
    ~Room();
    int getX() {return _x;} 
    int getY() {return _y;}
    int getW() {return _w;}
    int getH() {return _h;}
};

#endif
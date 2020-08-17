/************************************************************
 * Room.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef ROOM_H
#define ROOM_H

class Room{
private:
    int _x, _y;
    int _doors;    // Door Locations in Binary.  Top MSB - 1000, Clockwise
public:
    Room(int x, int y);
    ~Room();
};

Room::Room(int x, int y){
    this->_x = x;
    this->_y = y;
    this->_doors = 0b1010;
}

#endif
#include "Room.h"

Room::Room(int x, int y, int w, int h):
    _x(x), _y(y), _w(w), _h(h)
{
    
}

void Room::_generateDoors(int doors){
    int direction = rand() % 4;
    int location;
    switch (direction)
    {
    case 0:
        location = rand() % _w;
        break;
    case 1:
        location = rand() % _h;
        break;
    case 2:
        location = rand() % _w;
        break;
    default:
        location = rand() % _h;
        break;
    }
}
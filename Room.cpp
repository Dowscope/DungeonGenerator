#include "Room.h"

Room::Room(int x, int y, int w, int h):
    x(x), y(y), w(w), h(h)
{ 
    
}

void Room::generateDoor(){

    int direction = rand() % 4;
    int randomX = x + rand() % w;
    int randomY = y + rand() % h;

    switch (direction)
    {
    case 0:
        doorLocation = {randomX, y};
        break;
    case 1:
        doorLocation = {x+w-1, randomY};
        break;
    case 2:
        doorLocation = {randomX, y+h-1};
        break;
    default:
        doorLocation = {x, randomY};
        break;
    }
}
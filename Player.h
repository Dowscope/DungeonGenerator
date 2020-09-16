/************************************************************
 * Player.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef PLAYER_H
#define PLAYER_H

class Player{
private:
    int _x, _y;
public:
    Player(int x, int y);
    ~Player();
    int getX() {return _x;} 
    int getY() {return _y;}
    void setX(int newX) {_x = newX;}
    void setY(int newY) {_y = newY;}
};

#endif
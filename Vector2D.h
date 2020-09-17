/************************************************************
 * Vector2D.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

struct Vector2D{
    int x;
    int y;

    Vector2D();
    Vector2D(int x, int y);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

#endif
/************************************************************
 * Vector2D.h
 * Created by Tim Dowling
 * 
 * ***********************************************************/

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

struct Vector2D{
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

#endif
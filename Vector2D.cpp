#include "Vector2D.h"

Vector2D::Vector2D(): x(0.0f), y(0.0f) {}
Vector2D::Vector2D(float x, float y): x(x), y(y) {}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}
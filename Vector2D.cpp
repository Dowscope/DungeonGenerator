#include "Vector2D.h"

Vector2D::Vector2D(): x(0), y(0) {}
Vector2D::Vector2D(int x, int y): x(x), y(y) {}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}
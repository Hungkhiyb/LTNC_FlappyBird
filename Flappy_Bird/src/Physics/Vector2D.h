#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
    public:
        int X, Y;

    public:
        Vector2D() {}
        Vector2D(int x, int y) :X(x), Y(y) {}
        ~Vector2D() {}

    public:
        inline Vector2D operator + (const Vector2D& v2) const
        {
            return Vector2D(this->X + v2.X, this->Y + v2.Y);
        }

        inline Vector2D operator - (const Vector2D& v2) const
        {
            return Vector2D(this->X - v2.X, this->Y - v2.Y);
        }

        inline Vector2D operator * (const float scalar) const
        {
            return Vector2D(this->X * scalar, this->Y * scalar);
        }

        inline Vector2D operator / (const float scalar) const
        {
            return Vector2D(this->X / scalar, this->Y / scalar);
        }

};

#endif // VECTOR2D_H

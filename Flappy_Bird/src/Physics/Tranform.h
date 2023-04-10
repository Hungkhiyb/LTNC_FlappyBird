#ifndef TRANFORM_H
#define TRANFORM_H

#include <string>
#include "Vector2D.h"

class Tranform
{
    public:
        float X, Y;
        float VelX, VelY;

    public:
        Tranform(float x = 0, float y = 0, float velX = 0, float velY = 0) :X(x), Y(y), VelX(velX), VelY(velY) {}
        ~Tranform() {}

        inline void TranslateX(float x) { this->X += x; }
        inline void TranslateY(float y) { this->Y += y; }
        inline void Translate(Vector2D v) { this->X += v.X; this->Y += v.Y; }

        inline void TranslateVelX(float velX) { this->VelX += velX; }
        inline void TranslateVelY(float velY) { this->VelY += velY; }
};

#endif // TRANFORM_H

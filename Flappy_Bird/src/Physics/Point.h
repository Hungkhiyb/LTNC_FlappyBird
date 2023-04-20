#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        float X, Y;

        Point(int X = 0, int Y = 0) : X(X), Y(Y) {}
        ~Point() {}

        // addition +
        inline Point operator + (const Point& p2) const
        {
            return Point(X + p2.X, Y + p2.Y);
        }

        // addition +=
        inline friend Point operator += (Point& p1, const Point& p2)
        {
            p1.X += p2.X;
            p1.Y += p2.Y;
            return p1;
        }

        // subtraction -
        inline Point operator - (const Point& p2) const
        {
            return Point(X - p2.X, Y - p2.Y);
        }

        // subtraction -=
        inline friend Point operator -= (Point& p1, const Point& p2)
        {
            p1.X -= p2.X;
            p1.Y -= p2.Y;
            return p1;
        }


        // multiplication *
        inline Point operator * (const float scalar) const
        {
            return Point(X * scalar, Y * scalar);
        }

};

#endif // POINT_H

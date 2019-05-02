#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "ishape.h"

class triangle : public IShape
{
public:
    triangle(int id, int X1, int Y1, int X2, int Y2, int X3, int Y3);
    triangle(const triangle&) = delete;

    triangle& operator=(const triangle&) = delete;
    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;

    const int dots = 3;

    QPolygon frame;
};

#endif // TRIANGLE_H

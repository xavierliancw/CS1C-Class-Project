#ifndef SHAPERECT_H
#define SHAPERECT_H
#include "ishape.h"

class ShapeRect: public IShape
{
public:
    ShapeRect(int id, int originX, int originY, int width, int height);
    ShapeRect(const ShapeRect&) = delete;

    ShapeRect& operator=(const ShapeRect&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;

    QRect frame;
};

#endif // SHAPERECT_H

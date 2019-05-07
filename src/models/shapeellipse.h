#ifndef SHAPEELLIPSE_H
#define SHAPEELLIPSE_H

#include "ishape.h"
#include <cmath>

class ShapeEllipse : public IShape
{
public:
    const double pi = 3.14159265358979;
    QRect frame;

    ShapeEllipse(ShapeType shapeType, int originX, int originY, int height, int width);
    ShapeEllipse(const ShapeEllipse&) = delete;

    ShapeEllipse& operator = (const ShapeEllipse&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;
};

#endif // SHAPEELLIPSE_H

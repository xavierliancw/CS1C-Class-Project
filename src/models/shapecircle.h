#ifndef SHAPECIRCLE_H
#define SHAPECIRCLE_H
#include "shapeellipse.h"

class ShapeCircle: public ShapeEllipse
{
public:
    ShapeCircle(int x, int y, int diameter);
    ShapeCircle(const ShapeCircle&) = delete;

    ShapeCircle& operator = (const ShapeCircle&) = delete;

    virtual double perimeter() const;
    virtual double area() const;
};

#endif // SHAPECIRCLE_H

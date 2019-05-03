#ifndef SHAPECIRCLE_H
#define SHAPECIRCLE_H
#include "shapeellipse.h"

class ShapeCircle : public ShapeEllipse
{
public:
    ShapeCircle(int id, int x, int y, int radius);
    ShapeCircle(const ShapeCircle&) = delete;

    ShapeCircle& operator = (const ShapeCircle&) = delete;

    virtual double perimeter() const;
    virtual double area() const;

    int m_radius;
};





#endif // SHAPECIRCLE_H

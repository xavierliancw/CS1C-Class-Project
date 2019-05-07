#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shapepolygon.h"

class ShapeTriangle : public ShapePolygon
{
public:
    ShapeTriangle(int X1, int Y1, int X2, int Y2, int X3, int Y3);
    ShapeTriangle(const ShapeTriangle&) = delete;
    ShapeTriangle& operator=(const ShapeTriangle&) = delete;
};

#endif // TRIANGLE_H

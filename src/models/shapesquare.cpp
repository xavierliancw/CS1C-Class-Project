#include "shapesquare.h"

ShapeSquare::ShapeSquare(int originX, int originY, int sideLength):
    ShapeRect(IShape::ShapeType::Square, originX, originY, sideLength, sideLength)
{}

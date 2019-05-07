#include "shapetriangle.h"
#include <cmath>

ShapeTriangle :: ShapeTriangle(int X1, int Y1, int X2, int Y2, int X3, int Y3) :
    ShapePolygon(IShape::ShapeType::Triangle,QVector<QPoint>({QPoint(X1,Y1),QPoint(X2,Y2),QPoint(X3,Y3)}))
{}

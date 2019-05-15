#include "shapetriangle.h"
#include <cmath>

ShapeTriangle :: ShapeTriangle(const QPoint p1, const QPoint p2, const QPoint p3) :
    ShapePolygon(ShapeType::Triangle, QVector<QPoint>({p1, p2, p3}))
{
}

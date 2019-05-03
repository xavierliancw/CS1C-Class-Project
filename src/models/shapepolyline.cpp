#include "shapepolyline.h"

ShapePolyLine::ShapePolyLine(int id, int originX, int originY, int x2, int y2, int x3, int y3):
    IShape(id, ShapeType::Polyline)
{
   points.setPoints(count, originX, originY, x2, y2, x3, y3);

   count++;
}
void ShapePolyLine::draw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolyline(points);
}

void ShapePolyLine::move(int scootX, int scootY)
{
    points.translate(scootX, scootY);
}

double ShapePolyLine::perimeter(int originX, int originY, int x2, int y2, int x3, int y3) const
{
    points.point(1,int *x, int *y);
    return sqrt(pow((points.point(0,x,y) - points.x1()), 2) + pow((points.y2() - points.y1()), 2));
}

double ShapePolyLine::area() const
{
    return 0;
}

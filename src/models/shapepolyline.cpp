#include "shapepolyline.h"

ShapePolyLine::ShapePolyLine(IShape::ShapeType shapeType, QVector<QPoint> points):
    IShape(-1, shapeType)
{
   polyLine = QPolygon(points);
}

void ShapePolyLine::draw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolyline(polyLine);
}

void ShapePolyLine::move(int scootX, int scootY)
{
    polyLine.translate(scootX, scootY);
}

double ShapePolyLine::perimeter() const
{
    double perimeter = 0;

    if(polyLine.size() == 1)
    {
        perimeter = 0;
    }
    else
    {
        QPoint point1;
        QPoint point2;

        for(int i = 0; i < polyLine.size()-1; i++)
        {
            point1 = polyLine.point(i);
            point2 = polyLine.point(i + 1);

            perimeter += sqrt(pow((point2.x() - point1.x()), 2) + pow((point2.y() - point1.y()), 2));
        }
    }

    return perimeter;
}

double ShapePolyLine::area() const
{
    return 0;
}

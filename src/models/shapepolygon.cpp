#include "shapepolygon.h"

ShapePolygon :: ShapePolygon(int id, const QVector<QPoint>& points) : IShape(id, ShapeType::Polygon)
{
    poly = QPolygon(points);
}

void ShapePolygon :: draw(QPainter& painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolygon(poly);
}

void ShapePolygon :: move(int scootX, int scootY)
{
    poly.translate(scootX, scootY);
}

double ShapePolygon :: perimeter() const
{


}

double ShapePolygon :: area() const
{

}

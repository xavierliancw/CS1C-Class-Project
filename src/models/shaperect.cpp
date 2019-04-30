#include "shaperect.h"

ShapeRect::ShapeRect(int id, int originX, int originY, int width, int height):
    IShape(id, ShapeType::Rectangle)
{
    frame = QRect(originX, originY, width, height);
}

void ShapeRect::draw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(frame);
}

void ShapeRect::move(int scootX, int scootY)
{
    frame.setX(frame.x() + scootX);
    frame.setY(frame.y() + scootY);
}

double ShapeRect::perimeter() const
{
    return frame.height() * 2 + frame.width() * 2;
}

double ShapeRect::area() const
{
    return frame.height() * frame.width();
}

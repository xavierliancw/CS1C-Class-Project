#include "shaperect.h"

ShapeRect::ShapeRect(int id, int originX, int originY, int width, int height):
    IShape(id, ShapeType::Rectangle)
{
    frame = QRect(originX, originY, width, height);
}

void ShapeRect::draw(QPainter &painter)
{
    painter.drawRect(frame);
}


void ShapeRect::move()
{

}

float ShapeRect::perimeter() const
{

}

float ShapeRect::area() const
{

}

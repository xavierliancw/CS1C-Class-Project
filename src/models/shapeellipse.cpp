#include "shapeellipse.h"

ShapeEllipse::ShapeEllipse(ShapeType shapeType, int originX, int originY, int height, int width):
    IShape(-1, shapeType),
    frame(QRect(originX, originY, width, height))
{}

void ShapeEllipse::draw(QPainter& painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(frame);
}

void ShapeEllipse::move(int scootX, int scootY)
{
    frame.translate(scootX, scootY);
}

double ShapeEllipse::perimeter() const
{
    double first = (2 * pi);
    double secondNumerator = (pow((frame.height()/2),2) + pow((frame.width()/2),2));
    double secondDenominator = 2;
    double second = sqrt(secondNumerator / secondDenominator);
    double ret = (first * second);

    return ret;
}

double ShapeEllipse::area() const
{
    return (pi*(frame.height()/2)*(frame.width()/2));
}

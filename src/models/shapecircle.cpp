#include "shapecircle.h"

ShapeCircle::ShapeCircle(int x, int y, int diameter):
    ShapeEllipse(ShapeType::Circle, x, y, diameter, diameter)
{}

double ShapeCircle::perimeter() const
{
    return (2 * pi * (static_cast<double>(frame.height()) / 2));
}

double ShapeCircle::area() const
{
    return (pi * (pow((static_cast<double>(frame.height()) / 2), 2)));
}

#include "shapecircle.h"
#include<cmath>

ShapeCircle :: ShapeCircle(int id, int x, int y, int radius):
    ShapeEllipse (id,x,y,radius,radius)
{
    frame = QRect(x,y,radius,radius);
    m_radius = radius;
}

double ShapeCircle :: perimeter() const
{
    return (2*pi*m_radius);
}

double ShapeCircle :: area() const
{
    return (pi * (pow(m_radius ,2)));
}

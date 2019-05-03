#include "shapeline.h"
#include <QLine>
#include <QPoint>
#include <cmath>

ShapeLine::ShapeLine(int id, int x1, int y1, int x2, int y2):
    IShape(id, ShapeType::Line)
{
    line = QLine(x1, y1, x2, y2);
}

void ShapeLine::draw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawLine(line);
}

void ShapeLine::move(int scootX, int scootY)
{
    line.setP1(QPoint(line.x1() + scootX, line.y1() + scootY));
    line.setP2(QPoint(line.x2() + scootX, line.y2() + scootY));
}

double ShapeLine::perimeter() const
{
    return sqrt(pow((line.x2() - line.x1()), 2) + pow((line.y2() - line.y1()), 2));
}

double ShapeLine::area() const
{
    return 0;
}

#include "shapeline.h"
#include <QLine>
#include <QPoint>
#include <cmath>

ShapeLine::ShapeLine(int id, int originX, int originY, int x2, int y2):
    IShape(id, ShapeType::Line)
{
    frame = QLine(originX, originY, x2, y2);
}

void ShapeLine::draw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawLine(frame);
}

void ShapeLine::move(int scootX, int scootY)
{
    frame.setP1(QPoint(frame.x1() + scootX, frame.y1() + scootY));
    frame.setP2(QPoint(frame.x2() + scootX, frame.y2() + scootY));
}

double ShapeLine::perimeter() const
{
    return sqrt(pow((frame.x2() - frame.x1()), 2) + pow((frame.y2() - frame.y1()), 2));
}

double ShapeLine::area() const
{
    return 0;
}

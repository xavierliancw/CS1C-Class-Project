#include "shapeline.h"
#include <QLine>
#include <QPoint>
#include <cmath>

ShapeLine::ShapeLine(int x1, int y1, int x2, int y2):
    ShapePolyLine(ShapeType::Line, QVector<QPoint>({QPoint(x1, y1), QPoint(x2, y2)}))
{}

void ShapeLine::draw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    QLine line(polyLine[0], polyLine[1]);
    painter.drawLine(line);
}

void ShapeLine::move(int scootX, int scootY)
{
    polyLine[0].setX(polyLine[0].x() + scootX);
    polyLine[0].setY(polyLine[0].y() + scootY);

    polyLine[1].setX(polyLine[1].x() + scootX);
    polyLine[1].setY(polyLine[1].y() + scootY);
}

double ShapeLine::perimeter() const
{
    QLine line(polyLine[0], polyLine[1]);
    return sqrt(pow((line.x2() - line.x1()), 2) + pow((line.y2() - line.y1()), 2));
}

double ShapeLine::area() const
{
    return 0;
}

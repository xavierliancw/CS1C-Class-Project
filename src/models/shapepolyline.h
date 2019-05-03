#ifndef SHAPEPOLYLINE_H
#define SHAPEPOLYLINE_H

#include "ishape.h"
#include <QVector>
#include <QPolygon>
#include <QPoint>

class ShapePolyLine: public IShape
{
public:
    ShapePolyLine(int id, int originX, int originY, int x2, int y2, int x3, int y3);
    ShapePolyLine(const ShapePolyLine&) = delete;

    ShapePolyLine& operator=(const ShapePolyLine&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter(int originX, int originY, int x2, int y2, int x3, int y3) const;
    virtual double area() const;

private:
    QPolygon points;

    int count = 0;
    int originX;
    int originY;
    int x2;
    int y2;
    int x3;
    int y3;

};

#endif // SHAPEPOLYLINE_H

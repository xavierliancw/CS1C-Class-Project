#ifndef SHAPEPOLYLINE_H
#define SHAPEPOLYLINE_H

#include "ishape.h"
#include <QVector>
#include <QPolygon>
#include <QPoint>
#include <cmath>

class ShapePolyLine: public IShape
{
public:
    ShapePolyLine(int id, QVector<QPoint>& points);
    ShapePolyLine(const ShapePolyLine&) = delete;

    ShapePolyLine& operator=(const ShapePolyLine&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;

private:
    QPolygon polyLine;
};

#endif // SHAPEPOLYLINE_H

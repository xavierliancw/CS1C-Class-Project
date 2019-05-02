#ifndef SHAPEPOLYGON_H
#define SHAPEPOLYGON_H
#include "ishape.h"

class ShapePolygon : public IShape
{
public:
    ShapePolygon(int id, const QVector<QPoint>& points);
    ShapePolygon(const ShapePolygon&) = delete;

    ShapePolygon& operator = (const ShapePolygon&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;

private:
    QPolygon poly;
};

#endif // SHAPEPOLYGON_H

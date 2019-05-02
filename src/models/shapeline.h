#ifndef SHAPELINE_H
#define SHAPELINE_H
#include "ishape.h"

class ShapeLine: public IShape
{
public:
    ShapeLine(int id, int originX, int originY, int x2, int y2);
    ShapeLine(const ShapeLine&) = delete;

    ShapeLine& operator=(const ShapeLine&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;

    QLine frame;
};
#endif // SHAPELINE_H

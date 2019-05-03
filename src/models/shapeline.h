#ifndef SHAPELINE_H
#define SHAPELINE_H
#include "ishape.h"

class ShapeLine: public IShape
{
public:
    ShapeLine(int id, int x1, int y1, int x2, int y2);
    ShapeLine(const ShapeLine&) = delete;

    ShapeLine& operator=(const ShapeLine&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;

private:
    QLine line;
};
#endif // SHAPELINE_H

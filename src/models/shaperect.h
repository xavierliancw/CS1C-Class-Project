#ifndef SHAPERECT_H
#define SHAPERECT_H
#include "ishape.h"

class ShapeRect: public IShape
{
public:
    ShapeRect(int id, int originX, int originY, int width, int height);

    virtual void draw(QPainter&);
    virtual void move();
    virtual float perimeter() const;
    virtual float area() const;

    QRect frame;
private:
};

#endif // SHAPERECT_H

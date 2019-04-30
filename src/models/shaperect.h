#ifndef SHAPERECT_H
#define SHAPERECT_H
#include "ishape.h"

class ShapeRect: public IShape
{
public:
    ShapeRect();

    virtual void draw(const int translate_x, const int translate_y);
    virtual void move();
    virtual float perimeter() const;
    virtual float area() const;

private:
};

#endif // SHAPERECT_H

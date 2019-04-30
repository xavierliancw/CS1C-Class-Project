#ifndef SHAPERECT_H
#define SHAPERECT_H
#include "ishape.h"

class ShapeRect: public IShape
{
public:
    ShapeRect(int id, int originX, int originY, int width, int height);
    ~ShapeRect();

    virtual void draw(QPainter*);
    virtual void move();
    virtual float perimeter() const;
    virtual float area() const;

    void erase(QPainter*);

    QRect frame;
private:
    QRect *drawnFrame;
};

#endif // SHAPERECT_H

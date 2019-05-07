#ifndef SHAPETEXT_H
#define SHAPETEXT_H
#include "ishape.h"
#include <QGraphicsTextItem>

class ShapeText : public IShape
{
public:
    QFont font;
    QString m_text = "";
    QPoint m_point;

    ShapeText(int originX, int originY, const QString& text);
    ShapeText(const ShapeText&) = delete;

    ShapeText& operator = (const ShapeText&) = delete;

    virtual void draw(QPainter&);
    virtual void move(int scootX, int scootY);
    virtual double perimeter() const;
    virtual double area() const;
};
#endif // SHAPETEXT_H

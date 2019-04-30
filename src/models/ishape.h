#ifndef ISHAPE_H
#define ISHAPE_H

#include <QPainter>

class IShape
{
public:
    int id;
    QPen pen;
    QBrush brush;

    enum class ShapeType {NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Text};

    IShape(int, ShapeType);
    IShape(const IShape&) = delete;
    virtual ~IShape();

    IShape& operator=(const IShape&) = delete;
    bool operator==(const IShape& other) const;
    bool operator!=(const IShape& other) const;
    bool operator<(const IShape& other) const;
    bool operator>(const IShape& other) const;
    bool operator<=(const IShape& other) const;
    bool operator>=(const IShape& other) const;

    ShapeType getShape() const;

    void resetToDefaultStyle();

    virtual void draw(QPainter&) = 0;
    virtual void move(int, int) = 0;
    virtual float perimeter() const = 0;
    virtual float area() const = 0;

private:
    ShapeType shapeType;
};

#endif // ISHAPE_H

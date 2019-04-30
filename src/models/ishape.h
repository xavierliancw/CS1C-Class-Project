#ifndef ISHAPE_H
#define ISHAPE_H

#include <QPainter>

class IShape
{
public:
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
    void setShape(ShapeType shape);
    const QPen& getPen() const;
    void setPen(Qt::GlobalColor clr, int width, Qt::PenStyle penStyle,
                Qt::PenCapStyle capStyle, Qt::PenJoinStyle joinStyle);
    void setPen(Qt::GlobalColor);
    const QBrush& getBrush() const;
    void setBrush(Qt::GlobalColor, Qt::BrushStyle);
    int getID() const;
    void setID(int);

    void resetToDefaultStyle();
    void drawRect(int width, int height);

    virtual void draw(QPainter*) = 0;
    virtual void move() = 0;
    virtual float perimeter() const = 0;
    virtual float area() const = 0;

private:
    int id;
    ShapeType shapeType;
    QPen pen;
    QBrush brush;
};

#endif // ISHAPE_H

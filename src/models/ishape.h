#ifndef ISHAPE_H
#define ISHAPE_H

#include <QPainter>

class IShape
{
public:
    enum class ShapeType {NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Text};

    IShape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::NoShape);
    virtual ~IShape();

    ShapeType get_shape() const;
    const QPen& get_pen() const;
    const QBrush& get_brush() const;

    void set_shape(ShapeType shape);
    void set_pen(Qt::GlobalColor, int width, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle);
    void set_pen(Qt::GlobalColor);
    void set_brush(Qt::GlobalColor, Qt::BrushStyle);

    void default_style();
    void draw_rect(int width, int height);

    virtual void draw(const int translate_x, const int translate_y) = 0;
    virtual void move() = 0;
    virtual void perimeter() = 0;
    virtual void area() = 0;

protected:
    QPainter& get_qpainter();

private:
    QPainter qpainter;

    int id;
    ShapeType shapeType;
    QPen pen;
    QBrush brush;
};

#endif // ISHAPE_H

IShape::~IShape()
{
    //Avoids out-of-line compiler warning
}

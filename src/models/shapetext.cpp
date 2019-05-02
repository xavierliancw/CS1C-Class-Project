#include "shapetext.h"

ShapeText :: ShapeText(int id, int originX, int originY, const QString& text) : IShape(id, ShapeType::Text)
{
    m_text = text;
    m_point = QPoint(originX, originY);
}

void ShapeText :: draw(QPainter& painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawText(m_point, m_text);
}

void ShapeText :: move(int scootX, int scootY)
{
    m_point = QPoint(m_point.x() + scootX, m_point.y() + scootY);
}

double ShapeText :: perimeter() const
{
    return 0;
}

double ShapeText :: area() const
{
    return 0;
}

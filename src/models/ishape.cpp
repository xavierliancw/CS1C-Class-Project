#include "ishape.h"
#include <QDebug>

IShape::IShape(int id, ShapeType shape)
{
    this->id = id;
    this->shapeType = shape;
    resetToDefaultStyle();
}

IShape::~IShape() {}

bool IShape::operator==(const IShape& other) const {return id == other.id;}

bool IShape::operator!=(const IShape& other) const {return id != other.id;}

bool IShape::operator<(const IShape& other) const {return id < other.id;}

bool IShape::operator>(const IShape& other) const {return id > other.id;}

bool IShape::operator<=(const IShape &other) const {return id <= other.id;}

bool IShape::operator>=(const IShape &other) const {return id >= other.id;}

IShape::ShapeType IShape::getShape() const {return shapeType;}

QString IShape::getShapeStr() const
{
    switch (shapeType)
    {
    case IShape::ShapeType::Line: return "Line";
    case IShape::ShapeType::Text: return "Text";
    case IShape::ShapeType::Circle: return "Circle";
    case IShape::ShapeType::Square: return "Square";
    case IShape::ShapeType::Ellipse: return "Ellipse";
    case IShape::ShapeType::NoShape: return "NoShape";
    case IShape::ShapeType::Polygon: return "Polygon";
    case IShape::ShapeType::Polyline: return "Polyline";
    case IShape::ShapeType::Triangle: return "Triangle";
    case IShape::ShapeType::Rectangle: return "Rectangle";
    }
}

void IShape::resetToDefaultStyle()
{
    pen = QPen();
    pen.setColor(Qt::GlobalColor::white);
    pen.setWidth(1);
    brush = QBrush();
    brush.setColor(Qt::GlobalColor::white);
}

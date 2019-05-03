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

IShape::ShapeType IShape::getShape() const{return shapeType;}

void IShape::resetToDefaultStyle()
{
    pen = QPen();
    pen.setColor(Qt::GlobalColor::white);
    pen.setWidth(1);
    brush = QBrush();
    brush.setColor(Qt::GlobalColor::white);
}

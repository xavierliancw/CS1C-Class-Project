#include "ishape.h"
#include <QDebug>

IShape::IShape(int id, ShapeType shape)
{
    this->id = id;
    this->shapeType = shape;
    this->pen = QPen();
    this->brush = QBrush();
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
    brush = QBrush();
}

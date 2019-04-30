#include "ishape.h"
#include <QDebug>

IShape::~IShape() {/*Avoids out-of-line compiler warning*/}

bool IShape::operator==(const IShape& other) const {return getID() == other.getID();}

bool IShape::operator!=(const IShape& other) const {return getID() != other.getID();}

bool IShape::operator<(const IShape& other) const {return getID() < other.getID();}

bool IShape::operator>(const IShape& other) const {return getID() > other.getID();}

bool IShape::operator<=(const IShape &other) const {return getID() <= other.getID();}

bool IShape::operator>=(const IShape &other) const {return getID() >= other.getID();}

IShape::ShapeType IShape::getShape() const{return shapeType;}
void IShape::setShape(ShapeType shape) {shapeType = shape;}

const QPen& IShape::getPen() const{return pen;}
void IShape::setPen(Qt::GlobalColor clr, int width, Qt::PenStyle penStyle,
                    Qt::PenCapStyle capStyle, Qt::PenJoinStyle joinStyle)
{
    pen.setColor(clr);
    pen.setWidth(width);
    pen.setStyle(penStyle);
    pen.setCapStyle(capStyle);
    pen.setJoinStyle(joinStyle);
}
void IShape::setPen(Qt::GlobalColor clr) {pen.setColor(clr);}

const QBrush& IShape::getBrush() const{return brush;}
void IShape::setBrush(Qt::GlobalColor clr, Qt::BrushStyle brushStyle)
{
    brush.setColor(clr);
    brush.setStyle(brushStyle);
}

int IShape::getID() const {return id;}

void IShape::resetToDefaultStyle()
{
    pen = QPen();
    brush = QBrush();
}

void IShape::drawRect(int width, int height)
{
    qDebug() << "yeah idk what this'll do yet"; //TODO
}

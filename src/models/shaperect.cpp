#include "shaperect.h"

ShapeRect::ShapeRect(int id, int originX, int originY, int width, int height):
    IShape(id, ShapeType::Rectangle)
{
    frame = QRect(originX, originY, width, height);
    drawnFrame = nullptr;
}

ShapeRect::~ShapeRect()
{
    delete drawnFrame;
    drawnFrame = nullptr;
}

void ShapeRect::draw(QPainter* painter)
{
    erase(painter);
    drawnFrame = new QRect(frame);
    painter->fillRect(*drawnFrame, Qt::GlobalColor::red);
    painter->drawRect(*drawnFrame);
}

void ShapeRect::erase(QPainter *painter)
{
    if (drawnFrame != nullptr)
    {
        painter->eraseRect(*drawnFrame);
        delete drawnFrame;
        drawnFrame = nullptr;
    }
}

void ShapeRect::move()
{

}

float ShapeRect::perimeter() const
{

}

float ShapeRect::area() const
{

}

#include "triangle.h"
#include <cmath>

triangle :: triangle(int id,int X1, int Y1, int X2, int Y2, int X3, int Y3) :
    IShape(id, ShapeType::Triangle)
{
        frame.setPoints(dots, X1, Y1, X2, Y2,X3, Y3);
}
void triangle :: draw(QPainter& painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolygon(frame);
}
void triangle :: move(int scootX, int scootY)
{
    frame.translate(scootX, scootY);
}

double triangle :: perimeter() const
{

    int pX1 = frame.point(0).x();
    int pY1 = frame.point(0).y();
    int pX2 = frame.point(1).x();
    int pY2 = frame.point(1).y();
    int pX3= frame.point(2).x();
    int pY3 = frame.point(2).y();

    double s1 = sqrt(pow((pX1-pX2),2) + pow((pY1-pY2),2));
    double s2 = sqrt(pow((pX2-pX3),2) + pow((pY2-pY3),2));
    double s3 = sqrt(pow((pX3-pX1),2) + pow((pY3-pY1),2));

    double perimeter = s1 + s2 + s3;
    return  perimeter;

}
double triangle :: area() const
{
    int pX1 = frame.point(0).x();
    int pY1 = frame.point(0).y();
    int pX2 = frame.point(1).x();
    int pY2 = frame.point(1).y();
    int pX3= frame.point(2).x();
    int pY3 = frame.point(2).y();

    double s1 = sqrt(pow((pX1-pX2),2) + pow((pY1-pY2),2));
    double s2 = sqrt(pow((pX2-pX3),2) + pow((pY2-pY3),2));
    double s3 = sqrt(pow((pX3-pX1),2) + pow((pY3-pY1),2));

    double p = (s1 + s2 + s3)/2;

    double area = sqrt(p * (p - s1) * (p - s2) * (p - s3));
    return area;

}

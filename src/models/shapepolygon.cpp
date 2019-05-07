#include "shapepolygon.h"
#include <cmath>

ShapePolygon :: ShapePolygon(IShape::ShapeType shapeType, const QVector<QPoint>& points): IShape(-1, shapeType)
{
    poly = QPolygon(points);
}

void ShapePolygon :: draw(QPainter& painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolygon(poly);
}

void ShapePolygon :: move(int scootX, int scootY)
{
    poly.translate(scootX, scootY);
}

double ShapePolygon :: perimeter() const
{
    double perim = 0;
    if(poly.size() != 1) // if a single point, perimeter is 0
    {
        QPoint p1; //first point for comparison
        QPoint p2; //second point for comparison
        for(int i = 0; i < poly.size()-1; ++i)
        {
            p1 = poly.point(i); //set p1 value
            p2 = poly.point(i + 1); //set p2 value

            //apply distance formula, add to total perimeter
            perim += sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));
        }
    }
    return perim;
}

double ShapePolygon :: area() const
{
    double area = 0;
    double* subArea = new double [poly.size()];
    double heightAvg = 0;
    double width = 0;

    if(poly.size() != 1) //if just a single point, area is 0;
    {
        QPoint p1; //first point for comparison
        QPoint p2; //second point for comparison

        for(int i = 0; i < poly.size()-1; ++i) //compare points
        {
            //set points to correct values
            p1 = poly.point(i);
            p2 = poly.point(i+1);
            //calculate avg height of p1 and p2
            heightAvg = ((p1.y() + p2.y())/2);
            //calculate width of p1 to p2
            width = p2.x() - p1.x();
            //store data for later calculation
            subArea[i] = heightAvg * width;
        }
        //repeat previous steps for the last point to the first point.
        p1 = poly.point(poly.size());
        p2 = poly.point(0);
        heightAvg = ((p1.y() + p2.y())/2);
        width = p2.x() - p1.x();
        subArea[poly.size()] = heightAvg * width;

        //calculate area by adding the sub areas
        for(int i = 0; i <poly.size(); ++i)
            area += subArea[i];
    }
    if(area < 0) //if area is negative, change to positive
        area = area*-1;
    return area;
}

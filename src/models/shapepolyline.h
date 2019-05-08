#ifndef SHAPEPOLYLINE_H
#define SHAPEPOLYLINE_H

#include "ishape.h"
#include <QVector>
#include <QPolygon>
#include <QPoint>
#include <cmath>

/**
 * @brief A shape that consists of lines between multiple vertices.
 *
 */
class ShapePolyLine: public IShape
{
public:
    QPolygon polyLine; /**< Holds the vertices of the polyline. */

    /**
     * @brief Constructor.
     *
     * @param shapeType: Specifies what kind of shape this is (necessary for shapes that subclass
     * this).
     * @param points: The vertices to initialize with.
     */
    ShapePolyLine(IShape::ShapeType shapeType, QVector<QPoint> points);
    /**
     * @brief Deleted copy constructor.
     *
     * @param Object to copy from.
     */
    ShapePolyLine(const ShapePolyLine&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param Object to copy from.
     * @return ShapePolyLine &operator
     */
    ShapePolyLine& operator=(const ShapePolyLine&) = delete;

    /**
     * @brief Renders the polyline through a given QPainter object.
     *
     * @param painter: The QPainter object.
     */
    virtual void draw(QPainter&);
    /**
     * @brief Translates without changing its size.
     *
     * @param scootX: X direction to scoot.
     * @param scootY: Y direction to scoot.
     */
    virtual void move(int scootX, int scootY);
    /**
     * @brief Calculates the perimeter of this shape (total length of this polyline).
     *
     * @return double
     */
    virtual double perimeter() const;
    /**
     * @brief Calculates the area of this line... which is 0 always...
     *
     * @return double
     */
    virtual double area() const;
};

#endif // SHAPEPOLYLINE_H

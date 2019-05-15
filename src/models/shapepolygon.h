#ifndef SHAPEPOLYGON_H
#define SHAPEPOLYGON_H
#include "ishape.h"

/**
 * @brief Polygon shape that can be drawn on the graphics canvas.
 *
 */
class ShapePolygon : public IShape
{
public:
    QPolygon poly; /**< Stores the vertices of this polygon. */

    /**
     * @brief Constructor.
     *
     * @param points: Vector of points that define the vertices of the polygon.
     */
    ShapePolygon(const ShapeType shapeType, const QVector<QPoint>& points);
    /**
     * @brief Deleted copy constructor
     *
     * @param ShapePolygon to copy from.
     */
    ShapePolygon(const ShapePolygon&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param ShapePolygon to copy from.
     * @return ShapePolygon &operator
     */
    ShapePolygon& operator = (const ShapePolygon&) = delete;

    /**
     * @brief Renders this polygon through a given QPainter object.
     *
     * @param The QPainter object that handles rendering shapes.
     */
    virtual void draw(QPainter&);
    /**
     * @brief Moves the polygon's coordinates a specified amount.
     *
     * @param scootX: Number of pixels to scoot this rectangle in the X direction.
     * @param scootY: Number of pixels to scoot this rectangle in the Y direction.
     */
    virtual void move(int scootX, int scootY);
    /**
     * @brief Calculates the perimeter of this polygon.
     *
     * @return double: The perimeter of the polygon in pixels.
     */
    virtual double perimeter() const;
    /**
     * @brief Calculates the area of this polygon.
     *
     * @return double: The area of the polygon in pixels.
     */
    virtual double area() const;
};

#endif // SHAPEPOLYGON_H

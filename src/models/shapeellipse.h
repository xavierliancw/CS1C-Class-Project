#ifndef SHAPEELLIPSE_H
#define SHAPEELLIPSE_H

#include "ishape.h"
#include <cmath>

class ShapeEllipse : public IShape
{
public:
    const double pi = 3.14159265358979 /**< stores generalized value of pi */;
    QRect frame; /**< Stores the origin and size of this ellipse */

    /**
     * @brief Constructor
     *
     * @param shapeType: the shape type
     * @param originX: Starting X pixel position of the origin
     * @param originY: Starting Y pixel position of the origin
     * @param height: starting height in pixels
     * @param width: starting width in pixels
     */
    ShapeEllipse(ShapeType shapeType, int originX, int originY, int height, int width);

    /**
     * @brief Deleted copy constructor.
     *
     * @param ShapeEllipse to copy from.
     */
    ShapeEllipse(const ShapeEllipse&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param ShapeEllipse to copy from
     * @return ShapeEllipse &operator
     */
    ShapeEllipse& operator = (const ShapeEllipse&) = delete;

    /**
     * @brief Renders this ellipse through a given QPainter object.
     *
     * @param The QPainter object that handles rendering shapes.
     */
    virtual void draw(QPainter&);
    /**
     * @brief Moves this ellipse's coordinates a specified amount.
     *
     * @param scootX: Number of pixel to scoot this frame in the X direction
     * @param scootY: Number of pixels to scoot this rectangle in the Y direction
     */
    virtual void move(int scootX, int scootY);

    /**
     * @brief Calculates the perimeter of this Ellipse.
     *
     * @return double: the perimeter of this Ellipse in pixels.
     */
    virtual double perimeter() const;

    /**
     * @brief Calculates area of this Ellipse
     *
     * @return double: the area of this Ellipse in pixels
     */
    virtual double area() const;
};

#endif // SHAPEELLIPSE_H

#ifndef SHAPECIRCLE_H
#define SHAPECIRCLE_H
#include "shapeellipse.h"

/**
 * @brief Circle shape that can be drawn on the graphics canvas
 */
class ShapeCircle: public ShapeEllipse
{
public:
    /**
     * @brief Constructor
     *
     * @param x: x coordinate of circle's origin
     * @param y: y coordinate of circle's origin
     * @param diameter: diamter of circle
     */
    ShapeCircle(int x, int y, int diameter);

    /**
     * @brief Deleted Copy Constructor
     *
     * @param ShapeCircle to copy from
     */
    ShapeCircle(const ShapeCircle&) = delete;

    /**
     * @brief Deleted copy assignment operator
     *
     * @param ShapeCircle to copy from.
     * @return ShapeCircle &operator
     */
    ShapeCircle& operator = (const ShapeCircle&) = delete;

    /**
     * @brief Calculates the perimeter of this circle
     *
     * @return double: the perimeter of this circle in pixels
     */
    virtual double perimeter() const;

    /**
     * @brief Caluclates the area of this circle
     *
     * @return double: the area of this circle in pixels^2
     */
    virtual double area() const;
};

#endif // SHAPECIRCLE_H

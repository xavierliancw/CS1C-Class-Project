#ifndef SHAPERECT_H
#define SHAPERECT_H
#include "ishape.h"

/**
 * @brief Rectangular shape that can be drawn on the graphics canvas.
 *
 */
class ShapeRect: public IShape
{
public:
    QRect frame; /**< Stores the origin and size of this rectangle. */

    /**
     * @brief Constructor.
     *
     * @param shapeType: The shape type.
     * @param originX Starting X pixel position of the origin.
     * @param originY Starting Y pixel position of the origin.
     * @param width Starting width in pixels.
     * @param height Starting height in pixels.
     */
    ShapeRect(IShape::ShapeType shapeType, int originX, int originY, int width, int height);
    /**
     * @brief Deleted copy constructor.
     *
     * @param ShapeRect to copy from.
     */
    ShapeRect(const ShapeRect&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param ShapeRect to copy from.
     * @return ShapeRect &operator
     */
    ShapeRect& operator=(const ShapeRect&) = delete;

    /**
     * @brief Renders this rectangle through a given QPainter object.
     *
     * @param The QPainter object that handles rendering shapes.
     */
    virtual void draw(QPainter&);
    /**
     * @brief Moves this rectangle's coordinates a specified amount.
     *
     * @param scootX: Number of pixels to scoot this rectangle in the X direction.
     * @param scootY: Number of pixels to scoot this rectangle in the Y direction.
     */
    virtual void move(int scootX, int scootY);
    /**
     * @brief Calculates the perimeter of this rectangle.
     *
     * @return double: The perimenter of this rectangle in pixels.
     */
    virtual double perimeter() const;
    /**
     * @brief Calculates the area of this rectangle.
     *
     * @return double: The area of this rectangle in pixels^2.
     */
    virtual double area() const;
};

#endif // SHAPERECT_H

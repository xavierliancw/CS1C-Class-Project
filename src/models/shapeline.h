#ifndef SHAPELINE_H
#define SHAPELINE_H
#include "shapepolyline.h"

/**
 * @brief Represents lines that can be modeled on the canvas.
 *
 */
class ShapeLine: public ShapePolyLine
{
public:
    /**
     * @brief Constructor.
     *
     * @param x1: Starting X coordinate.
     * @param y1: Starting Y coordinate.
     * @param x2: Ending X coordinate.
     * @param y2: Ending Y coordiante.
     */
    ShapeLine(int x1, int y1, int x2, int y2);
    /**
     * @brief Deleted copy constructor.
     *
     * @param Object to copy from.
     */
    ShapeLine(const ShapeLine&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param Object to copy from.
     * @return ShapeLine &operator
     */
    ShapeLine& operator=(const ShapeLine&) = delete;

    /**
     * @brief Renders this line on the canvas.
     *
     * @param painter: Handles rendering the line.
     */
    virtual void draw(QPainter&);
    /**
     * @brief Translates this line without changing its size.
     *
     * @param scootX: X direction to scoot.
     * @param scootY: Y direction to scoot.
     */
    virtual void move(int scootX, int scootY);
    /**
     * @brief Calculates the length of the line.
     *
     * @return double
     */
    virtual double perimeter() const;
    /**
     * @brief Always returns 0 because this is a line.
     *
     * @return double
     */
    virtual double area() const;
};

#endif // SHAPELINE_H

#ifndef SHAPESQUARE_H
#define SHAPESQUARE_H

#include "shaperect.h"

/**
 * @brief Model representing square shapes.
 *
 */
class ShapeSquare: public ShapeRect
{
public:
    /**
     * @brief Constructor.
     *
     * @param originX: X coordinate for top left of the square.
     * @param originY: Y coordinate for top left of the square.
     * @param sideLength: Length of the sides of the square.
     */
    ShapeSquare(int originX, int originY, int sideLength);
    /**
     * @brief Deleted copy constructor.
     *
     * @param Other square to copy from.
     */
    ShapeSquare(const ShapeSquare&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param Other square to copy from
     * @return ShapeSquare &operator
     */
    ShapeSquare& operator=(const ShapeSquare&) = delete;
};

#endif // SHAPESQUARE_H

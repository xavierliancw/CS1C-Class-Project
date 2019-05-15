#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "ishape.h"
#include "shapepolygon.h"

/**
 * @brief The model that represents a triangle.
 *
 */
class ShapeTriangle : public ShapePolygon
{
public:
    /**
     * @brief Constructor
     *
     * @param p1: Point 1.
     * @param p2: Point 2.
     * @param p3: Point 3.
     */
    ShapeTriangle(const QPoint p1, const QPoint p2, const QPoint p3);
    /**
     * @brief Deleted copy constructor.
     *
     * @param Object to copy from.
     */
    ShapeTriangle(const ShapeTriangle&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param Object to copy from
     * @return ShapeTriangle &operator
     */
    ShapeTriangle& operator=(const ShapeTriangle&) = delete;
};

#endif // TRIANGLE_H

#ifndef ISHAPE_H
#define ISHAPE_H

#include <QPainter>

/**
 * @brief This is the interface that abstracts all common operations for all supported shapes.
 * As such, all shapes subclasses this class.
 *
 */
class IShape
{
public:
    int id; /**< ID of the shape, doubling as layer ID where 0 is on the bottom-most layer. */
    QPen pen; /**< The QPen that provides some shape styling. */
    QBrush brush; /**< The QBrush that provides some shape styling. */

    /**
     * @brief Names for supported shape prototypes.
     *
     */
    enum class ShapeType {NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Text};

    /**
     * @brief Constructor.
     *
     * @param int Shape ID.
     * @param ShapeType Type of shape.
     */
    IShape(int, ShapeType);
    /**
     * @brief Deleted copy constructor.
     *
     * @param IShape to copy from.
     */
    IShape(const IShape&) = delete;
    /**
     * @brief Virtual desctructor.
     *
     */
    virtual ~IShape();

    /**
     * @brief Deleted copy assignment operator.
     *
     * @param IShape to copy from.
     * @return IShape &operator
     */
    IShape& operator=(const IShape&) = delete;
    /**
     * @brief Equivalence operator.
     *
     * @param other shape to compare against.
     * @return bool operator true when IDs are equal.
     */
    bool operator==(const IShape& other) const;
    /**
     * @brief Nonequivalence operator.
     *
     * @param other shape to compare against.
     * @return bool operator true when IDs are not equal.
     */
    bool operator!=(const IShape& other) const;
    /**
     * @brief Less than operator.
     *
     * @param other shape to compare against.
     * @return bool operator true when this ID is less than the other shape's ID.
     */
    bool operator<(const IShape& other) const;
    /**
     * @brief Greater than operator.
     *
     * @param other shape to campare against.
     * @return bool operator true when this ID is greater than the other shape's ID.
     */
    bool operator>(const IShape& other) const;
    /**
     * @brief Less than or equal to operator.
     *
     * @param other shape to compare against.
     * @return bool operator true when this ID is less than or greater than the other shape's ID.
     */
    bool operator<=(const IShape& other) const;
    /**
     * @brief Greater than or equal to operator.
     *
     * @param other shape to compare against.
     * @return bool operator true when this ID is greater than or equal to the other shape's ID.
     */
    bool operator>=(const IShape& other) const;

    /**
     * @brief Retrieves the type of shape this shape object is.
     *
     * @return ShapeType
     */
    ShapeType getShape() const;

    /**
     * @brief Resets the styling attributes to the default settings.
     *
     */
    void resetToDefaultStyle();

    /**
     * @brief Renders this shape by giving instructions to a given QPainter object.
     *
     * @param The QPainter object that will perform the rendering.
     */
    virtual void draw(QPainter&) = 0;
    /**
     * @brief Shifts this shape around given integer values.
     *
     * @param int Number of pixels to shift in the x direction.
     * @param int Number of pixels to shift in the y direction.
     */
    virtual void move(int, int) = 0;
    /**
     * @brief Calculates the perimeter of this shape.
     *
     * @return double: The perimeter of this shape in pixels.
     */
    virtual double perimeter() const = 0;
    /**
     * @brief Calculates the area of this shape.
     *
     * @return double: The area of this shape in pixels^2.
     */
    virtual double area() const = 0;

private:
    ShapeType shapeType; /**< The type of shape this shape represents. */
};

#endif // ISHAPE_H

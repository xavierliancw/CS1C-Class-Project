#ifndef SHAPETEXT_H
#define SHAPETEXT_H
#include "ishape.h"
#include <QGraphicsTextItem>

/**
 * @brief Text that can be rendered on the canvas
 */
class ShapeText : public IShape
{
public:
    QFont font;
    QString m_text = "";
    QPoint m_point;

    /**
     * @brief Constructor
     *
     * @param id: Determines which shapes overlap others on the canvas, (0 is closest to the back)
     * @param originX: Starting x pixel position of the origin
     * @param originY: Starting y pixel position of the origin
     * @param text: Text to be written to the canvas
     */
    ShapeText(int originX, int originY, const QString& text);

    /**
     * @brief Deleted Copy Constructor
     *
     * @param ShapteText to copy from
     */
    ShapeText(const ShapeText&) = delete;

    /**
     * @brief Deleted copy assignment operator
     *
     * @param ShapeText to copy from
     * @return ShapeText &operator
     */
    ShapeText& operator = (const ShapeText&) = delete;

    /**
     * @brief Renders this text through a given QPainter object.
     *
     * @param the QPainter object that handles rendering the shapes
     */
    virtual void draw(QPainter&);

    /**
     * @brief Moves text coordinates a specified amount.
     *
     * @param scootX: Numbers of pixels to scoot this text in the X direction.
     * @param scootY: Number of pixels to scoot this text in the Y direction.
     */
    virtual void move(int scootX, int scootY);

    /**
     * @brief Returns 0
     *
     * @return Returns 0
     */
    virtual double perimeter() const {return 0;}

    /**
     * @brief Returns 0
     *
     * @return Returns 0
     */
    virtual double area() const {return 0;}
};
#endif // SHAPETEXT_H

#ifndef LCSHAPELAYER_H
#define LCSHAPELAYER_H

#include <QWidget>
#include "models/ishape.h"
#include <functional>

namespace Ui {class LCShapeLayer;}

/**
 * @brief A cell for each row in the list that displays the shape layers next to the canvas.
 *
 */
class LCShapeLayer : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param parent: Parent pointer.
     */
    explicit LCShapeLayer(QWidget *parent = nullptr);
    /**
     * @brief Destructor.
     *
     */
    ~LCShapeLayer();

    /**
     * @brief Populates data and updates the cell UI.
     *
     * @param shapeData: The shape to populate data with.
     * @param onDeleteAction: The lambda to call when the delete button is pressed.
     * @param onEditAction: The lambda to call when the edit button is pressed.
     */
    void populateWith(const IShape* shapeData,
                      std::function<void(int)>onDeleteAction,
                      std::function<void(int)>onEditAction);

private:
    Ui::LCShapeLayer *ui;
    const IShape* currentShape;
    std::function<void(int)> onDeleteAct;
    std::function<void(int)> onEditAct;

    void reset();
};

#endif // LCSHAPELAYER_H

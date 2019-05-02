#ifndef DLGSHAPEADDERRECT_H
#define DLGSHAPEADDERRECT_H

#include "models/shaperect.h"
#include <QDialog>
#include <QIntValidator>
#include <functional>

namespace Ui {
class DLGShapeAdderRect;
}

/**
 * @brief Dialog that generates a rectangle shape in dynamic memory, returning a pointer to it
 * through a lambda initialized in its constructor.
 *
 */
class DLGShapeAdderRect : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent: Parent pointer.
     * @param rectResult: Callback for possible generated rectangle.
     */
    explicit DLGShapeAdderRect(QWidget *parent = nullptr,
                               std::function<void(ShapeRect*)> rectResult = [](ShapeRect*){});
    /**
     * @brief Destructor.
     *
     */
    ~DLGShapeAdderRect() override;

private:
    Ui::DLGShapeAdderRect *ui; /**< UI pointer. */
    std::function<void(ShapeRect*)> lambdaRectResult; /**< Callback lambda. */
    QIntValidator* intValidator; /**< Field validator object that forces only numeric input. */

    /**
     * @brief This updates the enable state of the add button.
     *
     */
    void updateAddBtEnableState();
    /**
     * @brief This dymaically generates a rectangle in memory if inputs are valid. It'll call
     * the callback lambda if successful.
     *
     */
    void giveDLGSummonerCreatedRectIfPossible();
};

#endif // DLGSHAPEADDERRECT_H

#ifndef DLGSHAPEADDERRECT_H
#define DLGSHAPEADDERRECT_H

#include "models/shaperect.h"
#include "models/shapesquare.h"
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
class DLGShapeGenEditRectangles : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Different modes this dialog can be in.
     *
     */
    enum Mode {RectCreate, SquareCreate};

    /**
     * @brief Constructor.
     *
     * @param parent: Parent pointer.
     * @param startingMode: Mode to start with (generate a rect or a square).
     * @param rectResult: Callback for possible generated shapes.
     */
    explicit DLGShapeGenEditRectangles(QWidget *parent = nullptr,
                                       Mode startingMode = RectCreate,
                                       std::function<void(IShape*)> rectResult = [](IShape*){});
    /**
     * @brief Destructor.
     *
     */
    ~DLGShapeGenEditRectangles() override;

private:
    Ui::DLGShapeAdderRect *ui; /**< UI pointer. */
    std::function<void(IShape*)> lambdaRectResult; /**< Callback lambda. */
    QIntValidator* intValidator; /**< Field validator object that forces only numeric input. */
    Mode currentDisplayMode; /** < The mode this dialog is currently in. */

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

    /**
     * @brief Looks at appropriate UI elements and determines if their inputs are appropriate to
     * generate a shape.
     * @return True if shape can be generated, false otherwise.
     */
    bool inputsAreValid();
};

#endif // DLGSHAPEADDERRECT_H

#ifndef DLGEDITORRECTFRAME_H
#define DLGEDITORRECTFRAME_H

#include "models/shaperect.h"
#include "models/shapesquare.h"
#include <QDialog>
#include <QIntValidator>
#include <functional>

namespace Ui {class DLGEditorRectFrame;}

/**
 * @brief Dialog that edits rects which allows for generating rectangles and circles.
 * This generates a rectangle shape in dynamic memory, returning a pointer to it
 * through a lambda callback initialized in its constructor.
 *
 */
class DLGEditorRectFrame : public QDialog
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
     * @param possRectToEdit: If this is passed in, then this dialog will be editing that shape
     * instead of generating a new shape.
     * @param startingMode: Mode to start with (generate a rect or a square).
     * @param rectResult: Callback for possible generated shapes.
     */
    explicit DLGEditorRectFrame(QWidget *parent = nullptr,
                                ShapeRect* possRectToEdit = nullptr,
                                Mode startingMode = RectCreate,
                                std::function<void(IShape*)> rectResult = [](IShape*){});
    /**
     * @brief Destructor.
     *
     */
    ~DLGEditorRectFrame() override;

private:
    Ui::DLGEditorRectFrame *ui; /**< UI pointer. */
    std::function<void(IShape*)> lambdaRectResult; /**< Callback lambda. */
    QIntValidator* intValidator; /**< Field validator object that forces only numeric input. */
    Mode currentDisplayMode; /** < The mode this dialog is currently in. */
    ShapeRect* possRectBeingEdited;

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

#endif // DLGEDITORRECTFRAME_H
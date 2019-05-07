#ifndef DLGSHAPEADDTRI_H
#define DLGSHAPEADDTRI_H

#include "models/triangle.h"
#include <QDialog>
#include <QIntValidator>
#include <functional>

namespace Ui {
class DLGShapeAdderTri;
}

/**
 * @brief Dialog that generates a rectangle shape in dynamic memory, returning a pointer to it
 * through a lambda initialized in its constructor.
 *
 */
class DLGShapeAdderTri : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent: Parent pointer.
     * @param rectResult: Callback for possible generated rectangle.
     */
    explicit DLGShapeAdderTri(QWidget *parent = nullptr,
                               std::function<void(triangle*)> TriResult = [](triangle*){});
    /**
     * @brief Destructor.
     *
     */
    ~DLGShapeAdderTri() override;

private:
    Ui::DLGShapeAdderTri *ui; /**< UI pointer. */
    std::function<void(triangle*)> lambdaTriResult; /**< Callback lambda. */
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
#endif // DLGSHAPEADDTRI_H

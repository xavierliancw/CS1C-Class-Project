#ifndef DLGSHAPEADDTRI_H
#define DLGSHAPEADDTRI_H

#include "models/shapetriangle.h"
#include <QDialog>
#include <QIntValidator>
#include <functional>
#include "viewmodels/vmeditorrectframe.h"

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
    explicit DLGShapeAdderTri(QWidget *parent,
                              IShape::ShapeType shapeTypeToGen,
                              std::function<void(IShape*)> dlgDidGiveTriResult);
    explicit DLGShapeAdderTri(QWidget *parent,
                                IShape *shapeToEdit);
    /**
     * @brief Destructor.
     *
     */
    ~DLGShapeAdderTri() override;

private:
    Ui::DLGShapeAdderTri *ui;
    QIntValidator* intValidator;
    std::function<void(IShape*)> dlgDidGiveTriResult;
    VMEditorRectFrame vm;

    VMEditorRectFrame initVM();
    void initGeneralUI();
};
#endif // DLGSHAPEADDTRI_H

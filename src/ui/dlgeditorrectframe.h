#ifndef DLGEDITORRECTFRAME_H
#define DLGEDITORRECTFRAME_H

#include "models/shaperect.h"
#include "models/shapesquare.h"
#include <QDialog>
#include <QIntValidator>
#include <functional>
#include "viewmodels/vmeditorrectframe.h"

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
     * @brief Constructor used for generating new shapes.
     *
     * @param parent: Parent pointer.
     * @param shapeTypeToGen: The kind of shape to generate.
     * @param rectResult: Callback for generated shapes.
     */
    explicit DLGEditorRectFrame(QWidget *parent,
                                IShape::ShapeType shapeTypeToGen,
                                std::function<void(IShape*)> dlgDidGiveRectResult);
    /**
     * @brief Constructor used for editing existing shapes.
     *
     * @param parent: Parent pointer.
     * @param shapeToEdit: The shape to edit.
     */
    explicit DLGEditorRectFrame(QWidget *parent,
                                IShape *shapeToEdit);
    /**
     * @brief Destructor.
     *
     */
    ~DLGEditorRectFrame() override;

private:
    Ui::DLGEditorRectFrame *ui;
    QIntValidator* intValidator;
    std::function<void(IShape*)> dlgDidGiveRectResult;
    VMEditorRectFrame vm;

    VMEditorRectFrame initVM();
    void initGeneralUI();
};

#endif // DLGEDITORRECTFRAME_H

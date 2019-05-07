#ifndef DLGEDITORVERTICES_H
#define DLGEDITORVERTICES_H

#include <QDialog>
#include <QDropEvent>
#include <functional>
#include <models/ishape.h>
#include <viewmodels/vmeditorvertices.h>
#include "ui/lceditvertex.h"

namespace Ui {class DLGEditorVertices;}

/**
 * @brief Dialog to edit vertices. Good for making polylines and polygons.
 *
 */
class DLGEditorVertices : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor to initialize mode that generates new shapes.
     *
     * @param parent: Parent pointer.
     * @param shapeTypeToGen: Kind of shape to generate.
     * @param dlgDidGenerateNewShape: New shape callback.
     */
    explicit DLGEditorVertices(QWidget *parent,
                               IShape::ShapeType shapeTypeToGen,
                               std::function<void(IShape*)>dlgDidGenerateNewShape);
    /**
     * @brief Constructor to initialize mode that edits an existing shape;
     *
     * @param parent: Parent pointer.
     * @param shapeToEdit: Shape to edit.
     */
    explicit DLGEditorVertices(QWidget *parent, IShape *shapeToEdit);
    /**
     * @brief Destructor.
     *
     */
    ~DLGEditorVertices() override;

protected:
    /**
     * @brief Event filter used for vertex dragging and dropping.
     *
     * @param object: Object that event is happening to.
     * @param event: Event that's happening.
     * @return bool: Whatever super implementation returns.
     */
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Ui::DLGEditorVertices *ui;
    /**
     * @brief
     *
     * @param
     * @return std::function<void >
     */
    std::function<void(IShape*)>dlgDidGenerateNewShape;
    VMEditorVertices vm;
    bool deleteBtsEnabled = false;
    int rowNumberFromPickUpEvent = -1;
    QVector<LCEditVertex*> vertexEditCells;

    VMEditorVertices initVM();
    void initRestOfUI();
    void refreshListVw();
};

#endif // DLGEDITORVERTICES_H

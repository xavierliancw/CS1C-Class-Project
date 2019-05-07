#ifndef VMEDITORVERTICES_H
#define VMEDITORVERTICES_H

#include <QDebug>
#include <QPoint>
#include <QString>
#include <QVector>
#include <functional>
#include <tuple>
#include "models/ishape.h"
#include "models/shapepolygon.h"

class VMEditorVertices
{
public:
    VMEditorVertices(std::function<void(bool)>vmDidHideAddVertexBt,
                     std::function<void(bool)>vmDidEnableSubmitBt,
                     std::function<void()>vmDidRefreshUI,
                     std::function<void(IShape*)>vmDidGenerateNewShape,
                     std::function<void(bool)>vmDidDisableVertexDeleting);

    void resetStateUsing(IShape* shapeToBeEdited);
    void resetStateUsing(IShape::ShapeType shapeTypeToGenerate);

    QString getLblTxtTitle() const;
    QString getBtTxtCancel() const;
    QString getBtTxtSubmit() const;

    void finishEditing();
    void reorderVertex(int fromIndex, int toDestIndex);
    void createVertex();
    std::tuple<QString, QString> readVertextAt(int index) const;
    void updateVertexAt(int index, QString newX, QString newY);
    void removeVertexAt(int index);

private:
    enum Mode {addPolygon, editPolygon,
               addTriangle, editTriangle,
               addPolyline, editPolyline,
               addLine, editLine,
               noMode};

    std::function<void(bool)>vmDidHideAddVertexBt;
    std::function<void(bool)>vmDidEnableSubmitBt;
    std::function<void()>vmDidRefreshUI;
    std::function<void(IShape*)>vmDidGenerateNewShape;
    std::function<void(bool)>vmDidDisableVertexDeleting;

    QVector<std::tuple<QString, QString>> vertices;
    IShape* shapeBeingEdited = nullptr;
    Mode currentEditMode = noMode;

    IShape* generateNewShape();
    void applyState();
};

#endif // VMEDITORVERTICES_H

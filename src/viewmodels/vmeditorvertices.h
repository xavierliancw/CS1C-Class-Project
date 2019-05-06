#ifndef VMEDITORVERTICES_H
#define VMEDITORVERTICES_H

#include <QPoint>
#include <QString>
#include <QVector>
#include <functional>

class VMEditorVertices
{
public:
    VMEditorVertices();

    enum Mode {addPolygon, editPolygon,
               addTriangle, editTriangle,
               addPolyline, editPolyline,
               addLine, editLine};

    QString getLblTxtTitle() const;
    QString getLblTxtVertexAmtPrompt() const;
    QString getBtTxtCancel() const;
    QString getBtTxtSubmit() const;

    void reorderVertex(int fromIndex, int toDestIndex);

private:
    std::function<void(int)>vmDidSetVertexSpinBoxValue;
    std::function<void(bool)>vmDidHideVertexSpinBox;
    std::function<void(bool)>vmDidEnableSubmitBt;

    QVector<QPoint> vertices;
};

#endif // VMEDITORVERTICES_H

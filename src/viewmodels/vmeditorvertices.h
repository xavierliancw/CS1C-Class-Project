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
#include "models/shapepolyline.h"
#include "models/shapeline.h"
#include "models/shapetriangle.h"

/**
 * @brief View model that contains the state machine for editing shapes that are vertex based.
 *
 */
class VMEditorVertices
{
public:
    /**
     * @brief Constructor.
     *
     * @param vmDidHideAddVertexBt: Dictates whether the add button should be hidden or not.
     * @param vmDidEnableSubmitBt: Dictates whether the submit button should be enabled or not.
     * @param vmDidProvideStartingUIState: Provides stuff necessary to style the UI on init.
     * @param vmDidGenerateNewShape: Callback for when a new shape is generated.
     * @param vmDidDisableVertexDeleting: Controls when deleting vertices is disabled or not.
     * @param vmDidRefreshVertexList: Controls when the vertex list should be refreshed.
     */
    VMEditorVertices(std::function<void(bool)>vmDidHideAddVertexBt,
                     std::function<void(bool)>vmDidEnableSubmitBt,
                     std::function<void()>vmDidProvideStartingUIState,
                     std::function<void(IShape*)>vmDidGenerateNewShape,
                     std::function<void(bool)>vmDidDisableVertexDeleting,
                     std::function<void()>vmDidRefreshVertexList);

    /**
     * @brief Resets VM given a dependency.
     *
     * @param shapeToBeEdited: Triggers edit mode for this particular shape.
     */
    void resetStateUsing(IShape* shapeToBeEdited);
    /**
     * @brief Resets VM given a dependency.
     *
     * @param shapeTypeToGenerate: Triggers shape generation mode for this kind of shape.
     */
    void resetStateUsing(IShape::ShapeType shapeTypeToGenerate);

    /**
     * @brief Gets title string.
     *
     * @return QString
     */
    QString getLblTxtTitle() const;
    /**
     * @brief Gets cancel button text.
     *
     * @return QString
     */
    QString getBtTxtCancel() const;
    /**
     * @brief Gets submit button text for current mode.
     *
     * @return QString
     */
    QString getBtTxtSubmit() const;
    /**
     * @brief Gets number of vertices in memory.
     *
     * @return int
     */
    int getCurrentVertexCount() const;
    /**
     * @brief Retrieves a vertex at a specified index.
     *
     * @param index: The index to look at.
     * @return std::tuple<QString, QString>: The vertex.
     */
    std::tuple<QString, QString> getVertexAt(int index) const;

    /**
     * @brief Call this when user presses the submit button to finalize editing.
     *
     */
    void finishEditing();
    /**
     * @brief Moves a vertex to another spot to reorder the vertices.
     *
     * @param fromIndex: Index to move.
     * @param toDestIndex: Index to move to.
     */
    void reorderVertex(int fromIndex, int toDestIndex);
    /**
     * @brief Creates a blank vertex in memory.
     *
     */
    void createVertex();
    /**
     * @brief Retrieves a vertex from memory.
     *
     * @param index: Index to look in.
     * @return std::tuple<QString, QString>: The vertex data.
     */
    std::tuple<QString, QString> readVertextAt(int index) const;
    /**
     * @brief Updates the values for a vertex.
     *
     * @param index: The vertex to edit.
     * @param newX: New value for x coordinate.
     * @param newY: New value for y coordinate.
     */
    void updateVertexAt(int index, QString newX, QString newY);
    /**
     * @brief Removes a vertex from memory.
     *
     * @param index: The vertex number to remove.
     */
    void removeVertexAt(int index);

private:
    enum Mode {addPolygon, editPolygon,
               addTriangle, editTriangle,
               addPolyline, editPolyline,
               addLine, editLine,
               noMode};

    std::function<void(bool)>vmDidHideAddVertexBt;
    std::function<void(bool)>vmDidEnableSubmitBt;
    std::function<void()>vmDidProvideStartingUIState;
    std::function<void(IShape*)>vmDidGenerateNewShape;
    std::function<void(bool)>vmDidDisableVertexDeleting;
    std::function<void()>vmDidRefreshVertexList;

    QVector<std::tuple<QString, QString>> vertices;
    IShape* shapeBeingEdited = nullptr;
    Mode currentEditMode = noMode;

    IShape* generateNewShape();
    void applyState(bool justAddedVert, bool justRemovedVert, bool justInitialized);
    bool allCurrentVerticesAreValid();
};

#endif // VMEDITORVERTICES_H

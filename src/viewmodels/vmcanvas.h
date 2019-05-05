#ifndef VMCANVAS_H
#define VMCANVAS_H

#include "gimme.h"
#include "services/svcjson.h"
#include "models/jsonshape.h"
#include <util/goldenconevector.h>
#include <models/ishape.h>
#include <functional>
#include <QVector>
#include <QJsonValueRef>
#include <QJsonArray>

/**
 * @brief View model for the graphics canvas. This contains the resources and business logic for
 * the canvas UI.
 *
 */
class VMCanvas
{
public:
    /**
     * @brief Constructor.
     *
     * @param lambdaCanvasDidRefresh: Lambda to trigger a redraw of the canvas UI.
     * @param lambdaCanvasDidEditShapeAtLayer: Lambda to summon a shape editor form for the IShape.
     */
    VMCanvas(std::function<void(void)> lambdaCanvasDidRefresh,
             std::function<void(IShape*)> lambdaCanvasDidEditShapeAtLayer);

    /**
     * @brief Adds a shape to the canvas, assigning it a layer ID (AKA shape ID).
     *
     * @param shape: The shape to add.
     */
    void addShape(IShape* shape);
    /**
     * @brief Gets the number of shapes currently rendered on the canvas.
     *
     * @return unsigned int
     */
    int getNumberOfShapesOnCanvas() const;
    /**
     * @brief Gets a shape on the canvas.
     *
     * @param layerID: The layer to retrieve the shape from (AKA shapeID).
     * @return IShape
     */
    IShape* getShapeAtLayer(int layerID);
    /**
     * @brief Triggers an edit event of a shape on the canvas.
     *
     * @param layerID: The shape layer to edit.
     */
    void editShapeAtLayer(int layerID);
    /**
     * @brief Removes a shape from the canvas, updating all other shape layer IDs.
     * Nothing happens if the layer ID parameter is out of bounds.
     *
     * @param layerID: The shape layer to remove.
     */
    void removeShapeAtLayer(int layerID);
    /**
     * @brief Triggers a canvas redraw event so the UI can render whatever just changed.
     *
     */
    void updateCanvasToDisplayMostCurrentDrawing();
    /**
     * @brief Shifts a shape to a different layer, updating appropriate layer IDs.
     * Nothing happens if any of the parameters are out of bounds.
     *
     * @param layerID: The shape layer to shift.
     * @param destinationLayerID: The destination layer.
     */
    void changeShapeLayer(int layerID, int destinationLayerID);

    /**
     * @brief Saves the current state of user-generated graphics to persistent storage.
     */
    void persistCanvasToStorage();

private:
    /**
     * Holds all shapes on the canvas in memory. The order of the shapes in this vector matters
     * because index 0 represents layer 0, index 1 represents layer 1, and so on and so forth.
     * The shape at layer 0 is the bottom-most shape (it's underneath all the other shapes).
     */
    GoldenConeVector<IShape*> shapesInMemory;
    std::function<void(void)> lambdaCanvasDidRefresh; /** < Lambda that triggers canvas redraws. */
    /**
     * Lambda that triggers shape edit events.
     */
    std::function<void(IShape*)> lambdaCanvasDidEditShapeAtLayer;

    /**
     * @brief Validates if a layer ID is invalid (the ID is out of bounds of the shapes vector).
     *
     * @param layerID: The layer ID to check.
     * @return bool: True if layer ID in question does not exist, false otherwise.
     */
    bool invalid(int layerID);
    void loadSavedCanvasGraphicsFromStorage();
};

#endif // VMCANVAS_H

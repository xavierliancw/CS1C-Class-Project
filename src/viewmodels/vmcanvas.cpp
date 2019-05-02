#include "vmcanvas.h"

VMCanvas::VMCanvas(std::function<void(void)> lambdaCanvasDidRefresh,
                   std::function<void(IShape*)> lambdaCanvasDidEditShapeAtLayer)
{
    this->lambdaCanvasDidRefresh = lambdaCanvasDidRefresh;
    this->lambdaCanvasDidEditShapeAtLayer = lambdaCanvasDidEditShapeAtLayer;
}

void VMCanvas::addShape(IShape* shape)
{
    shape->id = shapesInMemory.size();  //Make sure to assign the layer ID
    shapesInMemory.push_back(shape);
    lambdaCanvasDidRefresh();
}

unsigned int VMCanvas::getNumberOfShapesOnCanvas() const
{
    return static_cast<unsigned int>(shapesInMemory.size());
}

IShape* VMCanvas::getShapeAtLayer(unsigned int layerID)
{
    if (invalid(layerID)) {return nullptr;}
    return shapesInMemory[layerID];
}

void VMCanvas::editShapeAtLayer(unsigned int layerID)
{
    if (invalid(layerID)) {return;}
    lambdaCanvasDidEditShapeAtLayer(shapesInMemory[layerID]);
}

void VMCanvas::removeShapeAtLayer(unsigned int layerID)
{
    if (invalid(layerID)) {return;}
    IShape** shapeToDelete = shapesInMemory.begin();
    shapeToDelete += layerID;
    shapesInMemory.erase(shapeToDelete);    //Delete the shape

    //Restore ID order
    for (unsigned int x = 0; x < static_cast<unsigned int>(shapesInMemory.size()); ++x)
    {
        shapesInMemory[x]->id = static_cast<int>(x);
    }
}

void VMCanvas::updateCanvasToDisplayMostCurrentDrawing()
{
    lambdaCanvasDidRefresh();
}

void VMCanvas::changeShapeLayer(unsigned int layerID, unsigned int destinationLayerID)
{
    //Make sure layer IDs are in bounds
    if (invalid(layerID) || invalid(destinationLayerID)) {return;}

    //Look at the shape that's going to be shifted
    IShape* shapeToShift = shapesInMemory[layerID];

    //"Remove" the shape (decrement all indices after layer ID)
    for (unsigned int x = layerID + 1;
         x < static_cast<unsigned int>(shapesInMemory.size());
         ++x)
    {
        shapesInMemory[x]->id -= 1;
    }
    //"Insert" the shape (increment all indices after destination ID)
    for (unsigned int x = destinationLayerID + 1;
         x < static_cast<unsigned int>(shapesInMemory.size());
         ++x)
    {
        shapesInMemory[x]->id += 1;
    }
    //Now "insert" the shape into its final destination
    shapeToShift->id = static_cast<int>(destinationLayerID);

    //Sort the vector to reorder the layers
    throw qt_error_string();    //TODO add in a sort to reorder the layers

    //Refresh the canvas to reflect the layer shift
    lambdaCanvasDidRefresh();
}

bool VMCanvas::invalid(unsigned int layerID)
{
    return shapesInMemory.size() == 0 ||
            layerID + 1 > static_cast<unsigned int>(shapesInMemory.size());
}

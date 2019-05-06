#include "vmcanvas.h"

VMCanvas::VMCanvas(std::function<void(void)> lambdaCanvasDidRefresh,
                   std::function<void(IShape*)> lambdaCanvasDidEditShapeAtLayer)
{
    this->lambdaCanvasDidRefresh = lambdaCanvasDidRefresh;
    this->lambdaCanvasDidEditShapeAtLayer = lambdaCanvasDidEditShapeAtLayer;

    try
    {
        loadSavedCanvasGraphicsFromStorage();
    }
    catch (SVCJson::JsonFileSystemError x)
    {/*Ignore this exception because the program will sometimes start with no saved file*/}
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
    delete shapesInMemory[layerID];         //Delete the shape
    shapesInMemory.erase(shapeToDelete);    //Remove the slot in the vector

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

void VMCanvas::persistCanvasToStorage()
{
    QJsonArray jsonArrayOfShapesToSave;

    //Serialize shapes to JSON
    for (IShape* saveThisShape: shapesInMemory)
    {
        jsonArrayOfShapesToSave.push_back(JSONShape::toJSON(saveThisShape));
    }
    //Save to memory
    SVCJson::getInstance()->
            persistJSONToLocalFileSystem(jsonArrayOfShapesToSave,
                                         Gimme::theShared()->fileNameForSavedGraphicsCanvas);
}

void VMCanvas::loadSavedCanvasGraphicsFromStorage()
{
    QJsonArray loadedJSONShapes;
    IShape* possRestoredShape = nullptr;
    QVector<IShape*> buildVect;

    //Load data from saved canvas file into memory
    loadedJSONShapes= SVCJson::getInstance()->
            readJsonArrayFile(Gimme::theShared()->fileNameForSavedGraphicsCanvas);

    //Regenerate shapes from the JSON
    for (QJsonValueRef jsonRef: loadedJSONShapes)
    {
        possRestoredShape = nullptr;    //Reset this every time to avoid duplicate shapes on fails
        if (jsonRef.isObject())
        {
            possRestoredShape = JSONShape::fromJSON(jsonRef.toObject());
        }
        if (possRestoredShape != nullptr)
        {
            buildVect.push_back(possRestoredShape);
        }
    }
    //Clear out memory in current canvas
    for (IShape* oldShape: shapesInMemory)
    {
        delete oldShape;
    }
    //Clear out current canvas
    IShape** delCursor = shapesInMemory.begin();
    while (delCursor != shapesInMemory.end())
    {
        shapesInMemory.erase(delCursor);
    }
    //Finally
    for (int x = 0; x < buildVect.size(); ++x)
    {
        //Make sure the IDs are contiguous and proper when importing
        buildVect[x]->id = x;

        //Move stuff from the built vector into canvas memory
        shapesInMemory.push_back(buildVect[x]);
    }
}

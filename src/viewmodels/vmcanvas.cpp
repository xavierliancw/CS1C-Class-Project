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

int VMCanvas::getNumberOfShapesOnCanvas() const
{
    return shapesInMemory.size();
}

IShape* VMCanvas::getShapeAtLayer(int layerID)
{
    if (invalid(layerID)) {return nullptr;}
    return shapesInMemory[static_cast<unsigned int>(layerID)];
}

void VMCanvas::editShapeAtLayer(int layerID)
{
    if (invalid(layerID)) {return;}
    lambdaCanvasDidEditShapeAtLayer(shapesInMemory[static_cast<unsigned int>(layerID)]);
}

void VMCanvas::removeShapeAtLayer(int layerID)
{
    if (invalid(layerID)) {return;}
    IShape** shapeToDelete = shapesInMemory.begin();
    shapeToDelete += layerID;
    delete shapesInMemory[static_cast<unsigned int>(layerID)];  //Delete the shape
    shapesInMemory.erase(shapeToDelete);                        //Remove the slot in the vector

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

void VMCanvas::changeShapeLayer(int layerID, int destinationLayerID)
{
    //When something's negative, it means the user dragged the shape to an invalid spot.
    //Return early here to avoid the bound check error message
    if (layerID < 0 || destinationLayerID < 0) {return;}

    //Make sure layer IDs are in bounds
    if (invalid(layerID) || invalid(destinationLayerID))
    {
        qDebug() << "There are " << shapesInMemory.size() <<
                    " shapes in memory. Tried to access index " << layerID <<
                    " to put at destination " << destinationLayerID;
        return;
    }
    QVector<IShape*> tempVect;
    for (int x = 0; x < shapesInMemory.size(); ++x)
    {
        tempVect.push_back(shapesInMemory[static_cast<unsigned int>(x)]);
    }
    tempVect.move(layerID, destinationLayerID);

    //Don't do any of this stuff if the vector is empty
    if (shapesInMemory.size() > 0)
    {
        //Clear shapes in memory
        IShape** delCursor = shapesInMemory.end() - 1;
        while (delCursor > shapesInMemory.begin() - 1)
        {
            shapesInMemory.erase(delCursor);
            delCursor--;
        }
        //Move them back from the temp vector
        for (int x = 0; x < tempVect.size(); ++x)
        {
            tempVect[x]->id = x;
            shapesInMemory.push_back(tempVect[x]);
        }
    }
    //Refresh the canvas to reflect the layer shift
    lambdaCanvasDidRefresh();
}

bool VMCanvas::invalid(int layerID)
{
    return shapesInMemory.size() == 0 ||
            layerID + 1 > shapesInMemory.size() ||
            layerID < 0;
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

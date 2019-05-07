#include "vmeditorvertices.h"

VMEditorVertices::VMEditorVertices(std::function<void(bool)>vmDidHideAddVertexBt,
                                   std::function<void(bool)>vmDidEnableSubmitBt,
                                   std::function<void()>vmDidProvideStartingUIState,
                                   std::function<void(IShape*)>vmDidGenerateNewShape,
                                   std::function<void(bool)>vmDidDisableVertexDeleting,
                                   std::function<void()>vmDidRefreshVertexList):
    vmDidHideAddVertexBt(vmDidHideAddVertexBt),
    vmDidEnableSubmitBt(vmDidEnableSubmitBt),
    vmDidProvideStartingUIState(vmDidProvideStartingUIState),
    vmDidGenerateNewShape(vmDidGenerateNewShape),
    vmDidDisableVertexDeleting(vmDidDisableVertexDeleting),
    vmDidRefreshVertexList(vmDidRefreshVertexList)
{}

void VMEditorVertices::resetStateUsing(IShape *shapeToBeEdited)
{
    shapeBeingEdited = shapeToBeEdited;
    vertices.clear();
    if (shapeToBeEdited == nullptr)
    {
        currentEditMode = noMode;
    }
    else
    {
        switch (shapeBeingEdited->getShape())
        {
        case IShape::ShapeType::Polygon:
            currentEditMode = editPolygon;
            if (ShapePolygon* castedPoly = dynamic_cast<ShapePolygon*>(shapeToBeEdited))
            {
                for (QPoint vert: castedPoly->poly)
                {
                    this->vertices.push_back(std::make_tuple(QString::number(vert.x()),
                                                             QString::number(vert.y())));
                }
            }
            break;
        case IShape::ShapeType::Triangle:
            currentEditMode = editTriangle;
            qDebug() << "Triangle editing not implemented yet.";
            break;
        case IShape::ShapeType::Polyline:
            currentEditMode = editPolyline;
            qDebug() << "Polyline editing not implemented yet.";
            break;
        case IShape::ShapeType::Line:
            currentEditMode = editLine;
            qDebug() << "Line editing not implemented yet.";
            break;
        default:
            currentEditMode = noMode;
            shapeBeingEdited = nullptr;
            qDebug() << shapeToBeEdited->getShapeStr() << "s cannot be edited here";
            break;
        }
    }
    applyState(true, false, true);
}

void VMEditorVertices::resetStateUsing(IShape::ShapeType shapeTypeToGenerate)
{
    switch (shapeTypeToGenerate)
    {
    case IShape::ShapeType::Polygon:
        currentEditMode = addPolygon;
        vertices.push_back(std::make_tuple("", ""));
        vertices.push_back(std::make_tuple("", ""));
        vertices.push_back(std::make_tuple("", ""));
        break;
    case IShape::ShapeType::Triangle:
        currentEditMode = addTriangle;
        vertices.push_back(std::make_tuple("", ""));
        vertices.push_back(std::make_tuple("", ""));
        vertices.push_back(std::make_tuple("", ""));
        break;
    case IShape::ShapeType::Polyline:
        currentEditMode = addPolyline;
        vertices.push_back(std::make_tuple("", ""));
        vertices.push_back(std::make_tuple("", ""));
        break;
    case IShape::ShapeType::Line:
        currentEditMode = addLine;
        vertices.push_back(std::make_tuple("", ""));
        vertices.push_back(std::make_tuple("", ""));
        break;
    default:
        currentEditMode = noMode;
        shapeBeingEdited = nullptr;
        qDebug() << "Tried to generate a shape that is unsupported by this shape editor";
        break;
    }
    applyState(true, false, true);
}

QString VMEditorVertices::getLblTxtTitle() const
{
    switch (currentEditMode)
    {
    case addPolygon: return "New Polygon";
    case editPolygon: return "Edit Polygon";
    case addTriangle: return "New Triangle";
    case editTriangle: return "Edit Triangle";
    case addPolyline: return "New Polyline";
    case editPolyline: return "Edit Polyline";
    case addLine: return "New Line";
    case editLine: return "Edit Line";
    case noMode: return "";
    }
}

QString VMEditorVertices::getBtTxtCancel() const
{
    return "Cancel";
}

QString VMEditorVertices::getBtTxtSubmit() const
{
    bool creating;
    switch (currentEditMode)
    {
    case addPolygon: creating = true; break;
    case editPolygon: creating = false; break;
    case addTriangle: creating = true; break;
    case editTriangle: creating = false; break;
    case addPolyline: creating = true; break;
    case editPolyline: creating = false; break;
    case addLine: creating = true; break;
    case editLine: creating = false; break;
    case noMode: creating = false; break;
    }
    if (creating) {return "Add";} else {return "Done";}
}

int VMEditorVertices::getCurrentVertexCount() const
{
    return vertices.size();
}

std::tuple<QString, QString> VMEditorVertices::getVertexAt(int index) const
{
    return vertices[index];
}


void VMEditorVertices::reorderVertex(int fromIndex, int toDestIndex)
{
    if (fromIndex > -1 && toDestIndex > -1 &&
            fromIndex < vertices.size() && toDestIndex < vertices.size())
    {
        vertices.move(fromIndex, toDestIndex);
    }
    applyState(true, true, false);
}

void VMEditorVertices::finishEditing()
{
    switch (currentEditMode)
    {
    case addPolygon:
        vmDidGenerateNewShape(generateNewShape());
        break;
    case addTriangle:
        vmDidGenerateNewShape(generateNewShape());
        break;
    case addPolyline:
        vmDidGenerateNewShape(generateNewShape());
        break;
    case addLine:
        vmDidGenerateNewShape(generateNewShape());
        break;
    case editPolygon:
        if (ShapePolygon* castedPoly = dynamic_cast<ShapePolygon*>(shapeBeingEdited))
        {
            castedPoly->poly.clear();
            for (std::tuple<QString, QString> vert: vertices)
            {
                castedPoly->poly.push_back(QPoint(std::get<0>(vert).toInt(),
                                                  std::get<1>(vert).toInt()));
            }
        }
        break;
    case editTriangle:
    case editPolyline:
    case editLine:
    case noMode:
        break;
    }
}

void VMEditorVertices::createVertex()
{
    vertices.push_back(std::make_tuple<QString, QString>("", ""));
    applyState(true, false, false);
}

std::tuple<QString, QString> VMEditorVertices::readVertextAt(int index) const
{
    return vertices.at(index);
}

void VMEditorVertices::updateVertexAt(int index, QString newX, QString newY)
{
    vertices.replace(index, std::make_tuple(newX, newY));
    applyState(false, false, false);
}

void VMEditorVertices::removeVertexAt(int index)
{
    vertices.removeAt(index);
    applyState(false, true, false);
}

IShape* VMEditorVertices::generateNewShape()
{
    if (vertices.isEmpty()) {return nullptr;}

    QVector<QPoint> finalVerts(vertices.size());
    bool intConversionSuccessful = true;
    int curX;
    int curY;

    //Convert vertices to QPoints
    for (std::tuple<QString, QString> rawVert: vertices)
    {
        curX = std::get<0>(rawVert).toInt(&intConversionSuccessful);
        curY = std::get<1>(rawVert).toInt(&intConversionSuccessful);
        if (!intConversionSuccessful) {return nullptr;} //Leave early since not all values are good
        finalVerts.append(QPoint(curX, curY));
    }
    switch (currentEditMode)
    {
    case addPolygon:
        if (finalVerts.size() > 2)
        {
            return new ShapePolygon(finalVerts);
        }
    case addTriangle:
    case addPolyline:
    case addLine:
    case editPolygon:
    case editTriangle:
    case editPolyline:
    case editLine:
    case noMode:
        break;
    }
    return nullptr;
}

void VMEditorVertices::applyState(bool justAddedVert, bool justRemovedVert, bool justInitialized)
{
    bool hideVertexAddBt = true;
    bool enableSubmitBt = false;
    bool disableVertexDeleting = true;

    switch (currentEditMode)
    {
    case addPolygon:
        //Polygons should always have the ability to add more points
        hideVertexAddBt = false;

        //Submit button is enabled when there are at least 3 verts and all verts are valid
        enableSubmitBt = vertices.size() > 2 && allCurrentVerticesAreValid();

        //Never allow the UI to drop below 4 points
        disableVertexDeleting = vertices.size() < 4;
        break;
    case addTriangle:
        //Triangles only have three fixed points, so prevent adding more
        hideVertexAddBt = true;

        //Submit button is enabled when there are 3 verts and all verts are valid
        enableSubmitBt = vertices.size() == 3 && allCurrentVerticesAreValid();

        //Fix the three points
        disableVertexDeleting = true;
        break;
    case addPolyline:
        hideVertexAddBt = false;
        enableSubmitBt = vertices.size() > 1 && allCurrentVerticesAreValid();
        disableVertexDeleting = vertices.size() < 3;
        break;
    case addLine:
        hideVertexAddBt = true;
        enableSubmitBt = vertices.size() == 2 && allCurrentVerticesAreValid();
        disableVertexDeleting = true;
        break;
    case editPolygon:
        hideVertexAddBt = false;
        enableSubmitBt = vertices.size() > 2 && allCurrentVerticesAreValid();
        disableVertexDeleting = vertices.size() < 4;
        break;
    case editTriangle:
        hideVertexAddBt = true;
        enableSubmitBt = vertices.size() == 3 && allCurrentVerticesAreValid();
        disableVertexDeleting = true;
        break;
    case editPolyline:
        hideVertexAddBt = false;
        enableSubmitBt = vertices.size() > 1 && allCurrentVerticesAreValid();
        disableVertexDeleting = vertices.size() < 3;
        break;
    case editLine:
        hideVertexAddBt = true;
        enableSubmitBt = vertices.size() == 2 && allCurrentVerticesAreValid();
        disableVertexDeleting = true;
        break;
    case noMode:
        hideVertexAddBt = true;
        enableSubmitBt = false;
        disableVertexDeleting = true;
        break;
    }
    if (justInitialized)
    {
        vmDidProvideStartingUIState();
    }
    if ((justAddedVert || justRemovedVert) && !justInitialized)
    {
        vmDidRefreshVertexList();
    }
    vmDidHideAddVertexBt(hideVertexAddBt);
    vmDidEnableSubmitBt(enableSubmitBt);
    vmDidDisableVertexDeleting(disableVertexDeleting);
}

bool VMEditorVertices::allCurrentVerticesAreValid()
{
    bool intConvertSuccess = true;
    for (std::tuple<QString, QString> pair: vertices)
    {
        std::get<0>(pair).toInt(&intConvertSuccess);
        std::get<1>(pair).toInt(&intConvertSuccess);
        if (!intConvertSuccess)
        {
            return false; //If any point is invalid return immediately
        }
    }
    return true;
}

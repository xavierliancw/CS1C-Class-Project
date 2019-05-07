#include "vmeditorrectframe.h"

VMEditorRectFrame::VMEditorRectFrame(std::function<void(bool)> vmDidSetSubmitBtEnabled,
                                     std::function<void(bool)> vmDidSetFourthPromptHidden,
                                     std::function<void(IShape*)> vmDidGenerateNewShape,
                                     std::function<QString()> vmDidWantRawX,
                                     std::function<QString()> vmDidWantRawY,
                                     std::function<QString()> vmDidWantRawW,
                                     std::function<QString()> vmDidWantRawH,
                                     std::function<void()> vmDidInitNewState):
    vmDidSetSubmitBtEnabled(vmDidSetSubmitBtEnabled),
    vmDidSetFourthPromptHidden(vmDidSetFourthPromptHidden),
    vmDidGenerateNewShape(vmDidGenerateNewShape),
    vmDidWantRawX(vmDidWantRawX),
    vmDidWantRawY(vmDidWantRawY),
    vmDidWantRawW(vmDidWantRawW),
    vmDidWantRawH(vmDidWantRawH),
    vmDidInitNewState(vmDidInitNewState)
{}

VMEditorRectFrame::~VMEditorRectFrame()
{
    delete finalizedFrame;
}

void VMEditorRectFrame::performActionsOnInputEdit()
{
    applyState(currentUIMode, false);
}

QString VMEditorRectFrame::getTxtLblTitle() const
{
    switch (currentUIMode)
    {
    case newRectangle: return "New Rectangle";
    case editRectangle: return "Rectangle Edit";
    case newSquare: return "New Square";
    case editSquare: return "Square Edit";
    case newEllipse: return "New Ellipse";
    case editEllipse: return "Ellipse Edit";
    case newCircle: return "New Circle";
    case editCicle: return "Circle Edit";
    case noMode: return "";
    }
}

QString VMEditorRectFrame::getTxtBtCancel() const
{
    return "Cancel";
}

QString VMEditorRectFrame::getTxtBtSubmit() const
{
    switch (currentUIMode)
    {
    case newRectangle: return "Add";
    case editRectangle: return "Apply";
    case newSquare: return "Add";
    case editSquare: return "Apply";
    case newEllipse: return "Add";
    case editEllipse: return "Apply";
    case newCircle: return "Add";
    case editCicle: return "Apply";
    case noMode: return "";
    }
}

QString VMEditorRectFrame::getTxtPrompt1() const
{
    return "X Coordinate: ";
}

QString VMEditorRectFrame::getTxtPrompt2() const
{
    return "Y Coordinate: ";
}

QString VMEditorRectFrame::getTxtPrompt3() const
{
    switch (currentUIMode)
    {
    case newRectangle: return "Width: ";
    case editRectangle: return "Width: ";
    case newSquare: return "Size: ";
    case editSquare: return "Size: ";
    case newEllipse: return "Width: ";
    case editEllipse: return "Width: ";
    case newCircle: return "Diameter: ";
    case editCicle: return "Diameter: ";
    case noMode: return "";
    }
}

QString VMEditorRectFrame::getTxtPrompt4() const
{
    switch (currentUIMode)
    {
    case newRectangle: return "Height: ";
    case editRectangle: return "Height: ";
    case newSquare: return "";
    case editSquare: return "";
    case newEllipse: return "Height: ";
    case editEllipse: return "Height: ";
    case newCircle: return "";
    case editCicle: return "";
    case noMode: return "";
    }
}

void VMEditorRectFrame::setModeWithDependency(IShape::ShapeType shapeTypeToGenerate)
{
    reset();
    switch (shapeTypeToGenerate)
    {
    case IShape::ShapeType::Rectangle:
        currentUIMode = newRectangle;
        break;
    case IShape::ShapeType::Square:
        currentUIMode = newSquare;
        break;
    case IShape::ShapeType::Ellipse:
        currentUIMode = newEllipse;
        break;
    case IShape::ShapeType::Circle:
        currentUIMode = newCircle;
        break;
    default:
        currentUIMode = noMode;
        qDebug() << "Tried to generate a shape that is unsupported by this shape editor";
        break;
    }
    applyState(currentUIMode, true);
}

void VMEditorRectFrame::setModeWithDependency(IShape* shapeToEdit)
{
    reset();
    if (shapeToEdit != nullptr)
    {
        shapeCurrentlyBeingEdited = shapeToEdit;
        switch (shapeToEdit->getShape())
        {
        case IShape::ShapeType::Rectangle:
            currentUIMode = editRectangle;
            if (ShapeRect* castedRect = dynamic_cast<ShapeRect*>(shapeToEdit))
            {
                rawX = QString::number(castedRect->frame.x());
                rawY = QString::number(castedRect->frame.y());
                rawW = QString::number(castedRect->frame.width());
                rawH = QString::number(castedRect->frame.height());
            }
            break;
        case IShape::ShapeType::Square:
            currentUIMode = editSquare;
            if (ShapeSquare* castedSquare = dynamic_cast<ShapeSquare*>(shapeToEdit))
            {
                rawX = QString::number(castedSquare->frame.x());
                rawY = QString::number(castedSquare->frame.y());
                rawW = QString::number(castedSquare->frame.width());
                rawH = QString::number(castedSquare->frame.height());
            }
            break;
        case IShape::ShapeType::Ellipse:
            currentUIMode = editEllipse;
            if (ShapeEllipse* castedEllipse = dynamic_cast<ShapeEllipse*>(shapeToEdit))
            {
                rawX = QString::number(castedEllipse->frame.x());
                rawY = QString::number(castedEllipse->frame.y());
                rawW = QString::number(castedEllipse->frame.width());
                rawH = QString::number(castedEllipse->frame.height());
            }
            break;
        case IShape::ShapeType::Circle:
            currentUIMode = editCicle;
            if (ShapeCircle* castedCircle = dynamic_cast<ShapeCircle*>(shapeToEdit))
            {
                rawX = QString::number(castedCircle->frame.x());
                rawY = QString::number(castedCircle->frame.y());
                rawW = QString::number(castedCircle->frame.width());
                rawH = QString::number(castedCircle->frame.height());
            }
            break;
        default:
            currentUIMode = noMode;
            shapeCurrentlyBeingEdited = nullptr;
            qDebug() << shapeToEdit->getShapeStr() << "s cannot be edited here";
            break;
        }
    }
    applyState(currentUIMode, true);
}

void VMEditorRectFrame::performActionsWhenDoneEditing()
{
    //No finalized frame means no shape gets edited or generated
    if (finalizedFrame == nullptr) {return;}
    switch (currentUIMode)
    {
    case newRectangle:
        vmDidGenerateNewShape(new ShapeRect(IShape::ShapeType::Rectangle,
                                            finalizedFrame->x(),
                                            finalizedFrame->y(),
                                            finalizedFrame->width(),
                                            finalizedFrame->height()));
        return;
    case editRectangle:
        if (ShapeRect* cast = dynamic_cast<ShapeRect*>(shapeCurrentlyBeingEdited))
        {
            cast->frame = *finalizedFrame;  //Value is copied
            return;
        }
        break;
    case newSquare:
        vmDidGenerateNewShape(new ShapeSquare(finalizedFrame->x(),
                                              finalizedFrame->y(),
                                              finalizedFrame->width()));
        return;
    case editSquare:
        if (ShapeSquare* cast = dynamic_cast<ShapeSquare*>(shapeCurrentlyBeingEdited))
        {
            cast->frame = *finalizedFrame;  //Value is copied
            return;
        }
        break;
    case newEllipse:
        vmDidGenerateNewShape(new ShapeEllipse(IShape::ShapeType::Ellipse,
                                               finalizedFrame->x(),
                                               finalizedFrame->y(),
                                               finalizedFrame->height(),
                                               finalizedFrame->width()));
        return;
    case editEllipse:
        if (ShapeEllipse* cast = dynamic_cast<ShapeEllipse*>(shapeCurrentlyBeingEdited))
        {
            cast->frame = *finalizedFrame;  //Value is copied
            return;
        }
        break;
    case newCircle:
        vmDidGenerateNewShape(new ShapeCircle(finalizedFrame->x(),
                                              finalizedFrame->y(),
                                              finalizedFrame->width()));
        return;
    case editCicle:
        if (ShapeCircle* cast = dynamic_cast<ShapeCircle*>(shapeCurrentlyBeingEdited))
        {
            cast->frame = *finalizedFrame;  //Value is copied
            return;
        }
        break;
    case noMode:
        break;
    }
}

void VMEditorRectFrame::applyState(Mode stateToApply, bool justInitialized)
{
    //Init general UI when specified
    if (justInitialized)
    {
        vmDidInitNewState();
    }
    //Show fourth prompt when appropriate
    bool hideFourthPrompt = true;
    switch (stateToApply)
    {
    case newRectangle: hideFourthPrompt = false; break;
    case editRectangle: hideFourthPrompt = false; break;
    case newSquare: hideFourthPrompt = true; break;
    case editSquare: hideFourthPrompt = true; break;
    case newEllipse: hideFourthPrompt = false; break;
    case editEllipse: hideFourthPrompt = false; break;
    case newCircle: hideFourthPrompt = true; break;
    case editCicle: hideFourthPrompt = true; break;
    case noMode: hideFourthPrompt = false; break;
    }
    vmDidSetFourthPromptHidden(hideFourthPrompt);

    //Generate finalized frame if possible (but delete the old one first if it's there)
    if (finalizedFrame != nullptr)
    {
        delete finalizedFrame;
        finalizedFrame = nullptr;
    }
    bool everyInputIsAValidInt = true;
    int x = vmDidWantRawX().toInt(&everyInputIsAValidInt);
    int y = vmDidWantRawY().toInt(&everyInputIsAValidInt);
    int w = vmDidWantRawW().toInt(&everyInputIsAValidInt);
    int h;
    if (currentUIMode == newSquare || currentUIMode == editSquare ||
            currentUIMode == newCircle || currentUIMode == editCicle)
    {
        h = w;
    }
    else
    {
        h = vmDidWantRawH().toInt(&everyInputIsAValidInt);
    }
    if (everyInputIsAValidInt)
    {
        finalizedFrame = new QRect(x, y, w, h);
    }
    //Update submit button state
    vmDidSetSubmitBtEnabled(finalizedFrame != nullptr);
}

void VMEditorRectFrame::reset()
{
    currentUIMode = noMode;
    rawX = "";
    rawY = "";
    rawW = "";
    rawH = "";
    shapeCurrentlyBeingEdited = nullptr;
    delete finalizedFrame;
    finalizedFrame = nullptr;
}

QString VMEditorRectFrame::getRawX() const
{
    return rawX;
}

QString VMEditorRectFrame::getRawY() const
{
    return rawY;
}

QString VMEditorRectFrame::getRawW() const
{
    return rawW;
}

QString VMEditorRectFrame::getRawH() const
{
    return rawH;
}

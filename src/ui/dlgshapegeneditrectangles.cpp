#include "dlgshapegeneditrectangles.h"
#include "ui_DLGShapeGenEditRectangles.h"

DLGShapeGenEditRectangles::DLGShapeGenEditRectangles(QWidget *parent,
                                                     ShapeRect* possRectToEdit,
                                                     Mode startingMode,
                                                     std::function<void(IShape*)> rectResult) :
    QDialog(parent),
    ui(new Ui::DLGShapeGenEditRectangles),
    possRectBeingEdited(possRectToEdit)
{
    ui->setupUi(this);

    //Initialize properties
    this->lambdaRectResult = rectResult;
    this->currentDisplayMode = startingMode;

    //Set up add button
    connect(ui->addBt, &QPushButton::clicked, ui->addBt, [this]()
    {
        giveDLGSummonerCreatedRectIfPossible();
        this->close();
    });
    //Set up cancel button
    connect(ui->cancelBt, &QPushButton::clicked, ui->cancelBt, [this]()
    {
        this->close();
    });
    //Have each field update state as text is typed
    connect(ui->field1LE, &QLineEdit::textChanged, ui->field1LE, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->field2LE, &QLineEdit::textChanged, ui->field2LE, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->field3LE, &QLineEdit::textChanged, ui->field3LE, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->field4LE, &QLineEdit::textChanged, ui->field4LE, [this]()
    {
        this->updateAddBtEnableState();
    });

    //Force fields to only except integers
    intValidator = new QIntValidator();
    ui->field1LE->setValidator(intValidator);
    ui->field2LE->setValidator(intValidator);
    ui->field3LE->setValidator(intValidator);
    ui->field4LE->setValidator(intValidator);

    //Set up UI
    ui->prompt1Lbl->setText("Top Left X Coordinate:");
    ui->prompt2Lbl->setText("Top Left Y Coordinate:");
    switch (currentDisplayMode)
    {
    case RectCreate:
        ui->titleLbl->setText("New Rectangle");
        ui->prompt3Lbl->setText("Width:");
        ui->prompt4Lbl->setText("Height:");
        break;
    case SquareCreate:
        ui->titleLbl->setText("New Square");
        ui->prompt3Lbl->setText("Size:");
        ui->prompt4Lbl->setText("This shouldn't show!");
        ui->prompt4Lbl->hide();
        ui->field4LE->hide();
        break;
    }
    //Initialize state
    updateAddBtEnableState();

    //Check if this dialog is going to be editing an existing shape
    if (this->possRectBeingEdited != nullptr)
    {
        //Set up for editing, prefilling fields with existing values
        ui->addBt->setText("Apply Changes");
        if (this->possRectBeingEdited->getShape() == IShape::ShapeType::Rectangle)
        {
            ui->titleLbl->setText("Edit Rectangle");
        }
        else {
            ui->titleLbl->setText("Edit Square");
        }
        ui->field1LE->setText(QString::number(possRectBeingEdited->frame.x()));
        ui->field2LE->setText(QString::number(possRectBeingEdited->frame.y()));
        ui->field3LE->setText(QString::number(possRectBeingEdited->frame.width()));
        ui->field4LE->setText(QString::number(possRectBeingEdited->frame.height()));
    }
}

DLGShapeGenEditRectangles::~DLGShapeGenEditRectangles()
{
    delete intValidator;
    delete ui;
}

void DLGShapeGenEditRectangles::updateAddBtEnableState()
{
    ui->addBt->setEnabled(inputsAreValid());
}

void DLGShapeGenEditRectangles::giveDLGSummonerCreatedRectIfPossible()
{
    if (this->possRectBeingEdited == nullptr)
    {
        //Create a new rect
        IShape* newRect = nullptr;

        //Generate rect is possible
        if (inputsAreValid())
        {
            //Determine what kind of rect to return
            switch (currentDisplayMode)
            {
            case RectCreate:
                newRect = new ShapeRect(IShape::ShapeType::Rectangle,
                                        ui->field1LE->text().toInt(),
                                        ui->field2LE->text().toInt(),
                                        ui->field3LE->text().toInt(),
                                        ui->field4LE->text().toInt());
                break;
            case SquareCreate:
                newRect = new ShapeSquare(ui->field1LE->text().toInt(),
                                          ui->field2LE->text().toInt(),
                                          ui->field3LE->text().toInt());
                break;
            }
        }
        lambdaRectResult(newRect);
        return;
    }
    else
    {
        //Return the edited rect
        this->possRectBeingEdited->frame.setX(ui->field1LE->text().toInt());
        this->possRectBeingEdited->frame.setY(ui->field2LE->text().toInt());
        this->possRectBeingEdited->frame.setWidth(ui->field3LE->text().toInt());
        switch (currentDisplayMode)
        {
        case RectCreate:
            this->possRectBeingEdited->frame.setHeight(ui->field4LE->text().toInt());
            break;
        case SquareCreate:
            this->possRectBeingEdited->frame.setHeight(ui->field3LE->text().toInt());
            break;
        }
        lambdaRectResult(this->possRectBeingEdited);
    }
}

bool DLGShapeGenEditRectangles::inputsAreValid()
{
    switch (currentDisplayMode)
    {
    case RectCreate:
        return !ui->field1LE->text().isEmpty() &&
                !ui->field2LE->text().isEmpty() &&
                !ui->field3LE->text().isEmpty() &&
                !ui->field4LE->text().isEmpty();
    case SquareCreate:
        return !ui->field1LE->text().isEmpty() &&
                !ui->field2LE->text().isEmpty() &&
                !ui->field3LE->text().isEmpty();
    }
}

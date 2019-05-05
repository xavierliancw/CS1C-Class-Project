#include "dlgshapegeneditrectangles.h"
#include "ui_dlgshapegeneditrectangles.h"

DLGShapeGenEditRectangles::DLGShapeGenEditRectangles(QWidget *parent,
                                                     Mode startingMode,
                                                     std::function<void(IShape*)> rectResult) :
    QDialog(parent),
    ui(new Ui::DLGShapeGenEditRectangles)
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

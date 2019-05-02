#include "dlgshapeadderrect.h"
#include "ui_dlgshapeadderrect.h"

DLGShapeAdderRect::DLGShapeAdderRect(QWidget *parent,
                                     std::function<void(ShapeRect*)> rectResult) :
    QDialog(parent),
    ui(new Ui::DLGShapeAdderRect)
{
    ui->setupUi(this);
    this->lambdaRectResult = rectResult;

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

    //Initialize state
    updateAddBtEnableState();
}

DLGShapeAdderRect::~DLGShapeAdderRect()
{
    delete intValidator;
    delete ui;
}

void DLGShapeAdderRect::updateAddBtEnableState()
{
    ui->addBt->setEnabled(!ui->field1LE->text().isEmpty() &&
                          !ui->field2LE->text().isEmpty() &&
                          !ui->field3LE->text().isEmpty() &&
                          !ui->field4LE->text().isEmpty());
}

void DLGShapeAdderRect::giveDLGSummonerCreatedRectIfPossible()
{
    //Validation systems in this class are already validating the input
    ShapeRect* newRect = new ShapeRect(-1,
                                       ui->field1LE->text().toInt(),
                                       ui->field2LE->text().toInt(),
                                       ui->field3LE->text().toInt(),
                                       ui->field4LE->text().toInt());
    lambdaRectResult(newRect);
}

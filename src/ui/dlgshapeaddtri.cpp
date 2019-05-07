#include "dlgshapeaddtri.h"
#include "ui_dlgshapeaddTri.h"

DLGShapeAdderTri::DLGShapeAdderTri(QWidget *parent,
                                     std::function<void(triangle*)> triResult) :
    QDialog(parent),
    ui(new Ui::DLGShapeAdderTri)
{
    ui->setupUi(this);
    this->lambdaTriResult = triResult;

    //Set up add button
    connect(ui->pushButton, &QPushButton::clicked, ui->pushButton, [this]()
    {
        giveDLGSummonerCreatedRectIfPossible();
        this->close();
    });
    //Set up cancel button
    connect(ui->pushButton_2, &QPushButton::clicked, ui->pushButton_2, [this]()
    {
        this->close();
    });
    //Have each field update state as text is typed
    connect(ui->lineEdit, &QLineEdit::textChanged, ui->lineEdit, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->lineEdit_2, &QLineEdit::textChanged, ui->lineEdit_2, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->lineEdit_3, &QLineEdit::textChanged, ui->lineEdit_3, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->lineEdit_4, &QLineEdit::textChanged, ui->lineEdit_4, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->lineEdit_5, &QLineEdit::textChanged, ui->lineEdit_5, [this]()
    {
        this->updateAddBtEnableState();
    });
    connect(ui->lineEdit_6, &QLineEdit::textChanged, ui->lineEdit_6, [this]()
    {
        this->updateAddBtEnableState();
    });

    //Force fields to only except integers
    intValidator = new QIntValidator();
    ui->lineEdit->setValidator(intValidator);
    ui->lineEdit_2->setValidator(intValidator);
    ui->lineEdit_3->setValidator(intValidator);
    ui->lineEdit_4->setValidator(intValidator);
    ui->lineEdit_5->setValidator(intValidator);
    ui->lineEdit_6->setValidator(intValidator);

    //Initialize state
    updateAddBtEnableState();
}

DLGShapeAdderTri::~DLGShapeAdderTri()
{
    delete intValidator;
    delete ui;
}

void DLGShapeAdderTri::updateAddBtEnableState()
{
    ui->pushButton->setEnabled(!ui->lineEdit->text().isEmpty() &&
                          !ui->lineEdit_2->text().isEmpty() &&
                          !ui->lineEdit_3->text().isEmpty() &&
                          !ui->lineEdit_4->text().isEmpty() &&
                          !ui->lineEdit_5->text().isEmpty() &&
                          !ui->lineEdit_6->text().isEmpty());
}

void DLGShapeAdderTri::giveDLGSummonerCreatedRectIfPossible()
{
    //Validation systems in this class are already validating the input
    triangle* newTri = new triangle(3,
                                       ui->lineEdit->text().toInt(),
                                       ui->lineEdit_2->text().toInt(),
                                       ui->lineEdit_3->text().toInt(),
                                       ui->lineEdit_4->text().toInt(),
                                       ui->lineEdit_5->text().toInt(),
                                       ui->lineEdit_6->text().toInt());
    lambdaTriResult(newTri);
}

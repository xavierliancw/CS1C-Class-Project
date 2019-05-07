#include "lcshapelayer.h"
#include "ui_lcshapelayer.h"

LCShapeLayer::LCShapeLayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LCShapeLayer)
{
    ui->setupUi(this);
    reset();

    connect(ui->editBt, &QPushButton::clicked, ui->editBt, [this]()
    {
        if (currentShape != nullptr)
        {
            onEditAct(currentShape->id);
        }
    });
    connect(ui->delBt, &QPushButton::clicked, ui->delBt, [this]()
    {
        if (currentShape != nullptr)
        {
            onDeleteAct(currentShape->id);
        }
    });
}

LCShapeLayer::~LCShapeLayer()
{
    reset();
    delete ui;
}

void LCShapeLayer::populateWith(const IShape* shapeData,
                                std::function<void(int)> onDeleteAction,
                                std::function<void(int)> onEditAction)
{
    reset();
    currentShape = shapeData;
    onDeleteAct = onDeleteAction;
    onEditAct = onEditAction;

    ui->idLbl->setText(QString::number(shapeData->id));
    ui->shapeLbl->setText(shapeData->getShapeStr());
}

void LCShapeLayer::reset()
{
    currentShape = nullptr;
    onDeleteAct = [](int){};
    onEditAct = [](int){};
    ui->idLbl->setText("");
    ui->shapeLbl->setText("");
}

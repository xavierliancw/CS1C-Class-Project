#include "lceditvertex.h"
#include "ui_lceditvertex.h"

LCEditVertex::LCEditVertex(QWidget *parent,
                           std::function<void(int, QString, QString)> onCoordUpdateAct,
                           std::function<void(int)> onDelBtPressForIndex) :
    QWidget(parent),
    ui(new Ui::LCEditVertex),
    coordUpdateAct(onCoordUpdateAct),
    delBtPressForIndex(onDelBtPressForIndex)
{
    ui->setupUi(this);

    //Live updates whenever text is changed
    connect(ui->leX, &QLineEdit::textChanged, ui->leX, [this]()
    {
        if (currentIndex != -1)
        {
            this->coordUpdateAct(this->currentIndex, ui->leX->text(), ui->leY->text());
        }
    });
    connect(ui->leY, &QLineEdit::textChanged, ui->leY, [this]()
    {
        if (currentIndex != -1)
        {
            this->coordUpdateAct(this->currentIndex, ui->leX->text(), ui->leY->text());
        }
    });

    //Force fields to only except integers
    intValidator = new QIntValidator();
    ui->leX->setValidator(intValidator);
    ui->leY->setValidator(intValidator);

    //Hook up delete button
    connect(ui->btDel, &QPushButton::clicked, ui->btDel, [this]()
    {
        if (currentIndex != -1)
        {
            this->delBtPressForIndex(currentIndex);
        }
    });
}

LCEditVertex::~LCEditVertex()
{
    delete intValidator;
    delete ui;
}

void LCEditVertex::populateWith(int indexNum, QString x, QString y, bool delBtEnabled)
{
    resetUI();
    this->currentIndex = indexNum;
    this->ui->lblNumber->setText("#" + QString::number(indexNum + 1));
    this->ui->leX->setText(x);
    this->ui->leY->setText(y);
    this->ui->btDel->setEnabled(delBtEnabled);
}

void LCEditVertex::resetUI()
{
    this->currentIndex = -1;
    this->ui->leX->setText("");
    this->ui->leY->setText("");
    this->ui->btDel->setEnabled(false);
}

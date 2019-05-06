#include "lceditvertex.h"
#include "ui_lceditvertex.h"

LCEditVertex::LCEditVertex(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LCEditVertex)
{
    ui->setupUi(this);
}

LCEditVertex::~LCEditVertex()
{
    delete ui;
}

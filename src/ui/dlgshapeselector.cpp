#include "dlgshapeselector.h"
#include "ui_dlgshapeselector.h"

DLGShapeSelector::DLGShapeSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGShapeSelector)
{
    ui->setupUi(this);
}

DLGShapeSelector::~DLGShapeSelector()
{
    delete ui;
}

void DLGShapeSelector::on_pushButton_clicked()
{
    close();
}

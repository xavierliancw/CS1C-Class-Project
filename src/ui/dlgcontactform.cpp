#include "dlgcontactform.h"
#include "ui_dlgcontactform.h"

DLGContactForm::DLGContactForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGContactForm)
{
    ui->setupUi(this);
}

DLGContactForm::~DLGContactForm()
{
    delete ui;
}

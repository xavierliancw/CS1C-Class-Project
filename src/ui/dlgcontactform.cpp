#include "dlgcontactform.h"
#include "ui_secdialog.h"

DLGContactForm::DLGContactForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
}

DLGContactForm::~DLGContactForm()
{
    delete ui;
}

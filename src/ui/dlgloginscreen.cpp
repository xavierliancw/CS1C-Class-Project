#include "dlgloginscreen.h"
#include "ui_dlgloginscreen.h"

DLGLoginScreen::DLGLoginScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGLoginScreen)
{
    ui->setupUi(this);
}

DLGLoginScreen::~DLGLoginScreen()
{
    delete ui;
}

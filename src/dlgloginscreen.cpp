#include "dlgloginscreen.h"
#include "ui_dlgloginscreen.h"
#include <QMessageBox>

DLGLoginScreen::DLGLoginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DLGLoginScreen)
{
    ui->setupUi(this);
}

DLGLoginScreen::~DLGLoginScreen()
{
    delete ui;
}

 bool DLGLoginScreen::check()
 {
     return administrator;
 }

void DLGLoginScreen::on_verifiy_clicked()
{
     bool verified = false;
    QString user = ui->username->text();
    QString pass = ui->password->text();

    if (user == "username" && pass == "password")
    {
        QMessageBox::information(this, "Login", "The username and password are correct");
        hide();
        verified = true;
    }
    else {

        QMessageBox::warning(this, "Login", "The username and password entered in are incorrect");
        verified = false;

    }

    administrator = verified;
}

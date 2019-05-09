#include "dlgloginscreen.h"
#include "ui_dlgloginscreen.h"
#include <QMessageBox>

DLGLoginScreen::DLGLoginScreen(QWidget *parent,
                               std::function<void()> authCallback) :
    QDialog(parent),
    ui(new Ui::DLGLoginScreen),
    authCallback(authCallback)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Sign In");
}

DLGLoginScreen::~DLGLoginScreen()
{
    delete ui;
}

//This is where the login screen inputs get checked to know whether or not to pull up the add shapes window
void DLGLoginScreen::on_verifiy_clicked()
{
    QString user = ui->username->text();
    QString pass = ui->password->text();

    if (user == "username" && pass == "password")
    {
        authCallback();
        close();
    }
    else
    {
        QMessageBox::warning(this, "Login", "The username and password entered in are incorrect");
    }
}

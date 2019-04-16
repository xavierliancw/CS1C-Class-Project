#include "winmain.h"
#include "ui_winmain.h"
#include "secdialog.h"

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain)
{
    ui->setupUi(this);
}

WINMain::~WINMain()
{
    delete ui;
}

void WINMain::on_pushButton_clicked()
{
    //SecDialog secdialog;
    //secdialog.setModal(true);
    //secdialog.exec();
    secdialog = new SecDialog(this);
    secdialog->show();
}

#include "winmain.h"
#include "ui_winmain.h"

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

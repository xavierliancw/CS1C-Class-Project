#include "dlgshapereport.h"
#include "ui_dlgshapereport.h"
#include "winmain.h"
#include "ui_winmain.h"

DLGShapeReport::DLGShapeReport(QWidget *parent,
                               std::function<void()> authCallback) :
    QDialog(parent),
    ui(new Ui::DLGShapeReport),
    authCallback(authCallback)
{
    ui->setupUi(this);
}

DLGShapeReport::~DLGShapeReport()
{
    delete ui;
}

void DLGShapeReport::saveToFile()
{
    QString filename = "Data.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "something" << endl;
    }
}

void DLGShapeReport::createShapeFileReport()
{
    //connect(WINMain::saveReport, SIGNAL(clicked()),this, SLOT(saveToFile()));
}

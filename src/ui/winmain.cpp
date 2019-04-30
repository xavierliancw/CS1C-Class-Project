#include "winmain.h"
#include "ui_winmain.h"

#include <models/dtotestimonial.h>
#include <models/jsontestimonial.h>

#include <services/svcjson.h>
#include <chrono>
#include<QJsonArray>
#include <QDebug>

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain)
{
    ui->setupUi(this);

    //UI behavior definitions
    connect(ui->TEMPBt, &QPushButton::clicked, ui->TEMPBt, [this]()
    {
        testimonialFormWin = new DLGTestimonialCreate();
        testimonialFormWin->setAttribute(Qt::WA_DeleteOnClose);
        testimonialFormWin->show();
    });

    connect(ui->TEMPBtDos, &QPushButton::clicked, ui->TEMPBtDos, [this]()
    {
        deletemelater = new DLGDeleteMeLater();
        deletemelater->setAttribute(Qt::WA_DeleteOnClose);
        deletemelater->show();
    });
}

WINMain::~WINMain()
{
    delete ui;
}

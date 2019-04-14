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
        if (testimonialFormWin == nullptr)
        {
            testimonialFormWin = new DLGTestimonialCreate();
        }
        testimonialFormWin->show();
    });
}

WINMain::~WINMain()
{
    delete ui;
}

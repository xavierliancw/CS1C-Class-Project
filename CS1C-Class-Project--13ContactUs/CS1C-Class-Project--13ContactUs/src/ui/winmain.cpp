#include "winmain.h"
#include "ui_winmain.h"

#include <models/dtotestimonial.h>
#include <models/jsontestimonial.h>

#include <services/svcjson.h>
#include <chrono>
#include<QJsonArray>

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain)
{
    ui->setupUi(this);

    //UI behavior definitions - Leave Feedback button
    connect(ui->TEMPBt, &QPushButton::clicked, ui->TEMPBt, [this]()
    {
        testimonialFormWin = new DLGTestimonialCreate();
        testimonialFormWin->setAttribute(Qt::WA_DeleteOnClose);
        testimonialFormWin->show();
    });

    //UI behavior definitions - Secondary Window
    connect(ui->contact_us, &QPushButton::clicked, ui->contact_us, [this]()
    {
        secdialog = new SecDialog();
        secdialog->setAttribute(Qt::WA_DeleteOnClose);
        secdialog->show();
    });

}

WINMain::~WINMain()
{
    delete ui;
}


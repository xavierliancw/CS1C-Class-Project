#include "winmain.h"
#include "ui_winmain.h"

#include <models/dtotestimonial.h>
#include <models/jsontestimonial.h>
#include <models/shapeellipse.h>
#include <util/conevector.h>

#include <services/svcjson.h>
#include <chrono>
#include<QJsonArray>

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain)
{
    ui->setupUi(this);

    //UI behavior definitions
    connect(ui->startBt, &QPushButton::clicked, ui->startBt, [this]()
    {
        this->ui->stackWdgt->setCurrentWidget(this->ui->canvasPg);
    });
    connect(ui->addTestimonialBt, &QPushButton::clicked, ui->addTestimonialBt, [this]()
    {
        testimonialFormWin = new DLGTestimonialCreate();
        testimonialFormWin->setAttribute(Qt::WA_DeleteOnClose);
        testimonialFormWin->show();
    });
    connect(ui->addBt, &QPushButton::clicked, ui->addBt, [this]()
    {
        ShapeEllipse *ellipse = new ShapeEllipse(0, 0, 0, 100, 200);
        ellipse->move(vect.size() * 3, 0);
//        ShapeRect *ellipse = new ShapeRect(0, 0, 0, 100, 200);
        ellipse->pen.setColor(Qt::GlobalColor::red);
        ellipse->pen.setWidth(12);
        vect.push_back(ellipse);
    });
}

WINMain::~WINMain()
{
    delete ui;

    for (int x = 0; x < vect.size(); ++x)
    {
        delete vect[x];
    }
}

void WINMain::paintEvent(QPaintEvent *event)
{
    QPainter painter(ui->canvasVw);

    for (unsigned int x = vect.size(); x > 0; --x)
    {
        vect[x - 1]->draw(painter);
    }
}

#include "winmain.h"
#include "ui_winmain.h"

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain)
{
    ui->setupUi(this);

    //UI behavior definitions
    initStartBt();
    initContactUsBt();
    initTestimonialCreateBt();

    //TODO move somewhere else later
    connect(ui->addBt, &QPushButton::clicked, ui->addBt, [this]()
    {
        ShapeCircle *ellipse = new ShapeCircle(0, 0, 0, 100);
        ellipse->move(vect.size() * 3, 0);
//        ShapeRect *ellipse = new ShapeRect(0, 0, 0, 100, 200);
        ellipse->pen.setColor(Qt::GlobalColor::red);
        ellipse->pen.setWidth(12);
        vect.push_back(ellipse);
    });
}

WINMain::~WINMain()
{
    //TODO move vector to VM
    for (int x = 0; x < vect.size(); ++x)
    {
        delete vect[static_cast<unsigned int>(x)];
    }
    delete ui;
}

void WINMain::paintEvent(QPaintEvent*)
{
    //Don't even think about drawing until we're on the canvas page
    if (ui->stackWdgt->currentWidget() != ui->canvasPg)
    {
        return;
    }
    //Instnantiate a painter that'll draw on the canvas view
    QPainter painter;

    //Begin by wiping all drawings
    painter.begin(ui->canvasVw);
    painter.fillRect(ui->canvasVw->rect(), Qt::GlobalColor::black);

    //Draw all shapes in memory (going backwards is important because 0 is lowest z-axis layer)
    for (int x = vect.size(); x > 0; --x)
    {
        vect[static_cast<unsigned int>(x) - 1]->draw(painter);
    }
    painter.end();
}

void WINMain::initStartBt()
{
    connect(ui->startBt, &QPushButton::clicked, ui->startBt, [this]()
    {
        this->ui->stackWdgt->setCurrentWidget(this->ui->canvasPg);
    });
}

void WINMain::initContactUsBt()
{
    connect(ui->contactBt, &QPushButton::clicked, ui->contactBt, [this]()
    {
        contactFormWin = new DLGContactForm();
        contactFormWin->setAttribute(Qt::WA_DeleteOnClose);
        contactFormWin->show();
    });
}

void WINMain::initTestimonialCreateBt()
{
    connect(ui->addTestimonialBt, &QPushButton::clicked, ui->addTestimonialBt, [this]()
    {
        testimonialFormWin = new DLGTestimonialCreate();
        testimonialFormWin->setAttribute(Qt::WA_DeleteOnClose);
        testimonialFormWin->show();
    });
}

#include "winmain.h"
#include "ui_winmain.h"

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain),
    vm(initVM())
{
    ui->setupUi(this);

    //UI behavior definitions
    initStartBt();
    initContactUsBt();
    initTestimonialCreateBt();

    connect(ui->addRectBt, &QPushButton::clicked, ui->addRectBt, [this]()
    {
        dlgAddShapeRect = new DLGShapeAdderRect(nullptr, [this](ShapeRect* rectIn)
        {
            this->vm.addShape(rectIn);
        });
        dlgAddShapeRect->setAttribute(Qt::WA_DeleteOnClose);
        dlgAddShapeRect->show();
    });
}

WINMain::~WINMain()
{
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
    for (unsigned int x = vm.getNumberOfShapesOnCanvas(); x > 0; --x)
    {
        vm.getShapeAtLayer(x - 1)->draw(painter);
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

VMCanvas WINMain::initVM()
{
    return VMCanvas([this]() {      //Lambda to refresh the canvas
        this->update();
        this->ui->canvasVw->update();
    },
    [this](IShape* shapeToEdit) {   //Lambda to edit a shape
        qDebug() << "gonna edit" << shapeToEdit->id;    //TODO
    });
}

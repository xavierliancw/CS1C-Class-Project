#include "winmain.h"
#include "ui_winmain.h"

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain),
    vm(initCanvasVM())
{
    ui->setupUi(this);

    //Initialize UI on welcome page
    initStartBt();
    initContactUsBt();
    initTestimonialCreateBt();

    //Initialze UI on the canvas page
    initCanvasBackBt();
    initAddRectBt();
    initAddSquareBt();

    switchScreenToShow(ScreensInWINMain::welcome);  //Force welcome screen on start
}

WINMain::~WINMain()
{
    delete ui;
}

void WINMain::closeEvent(QCloseEvent*)
{
    vm.persistCanvasToStorage();
}

void WINMain::paintEvent(QPaintEvent*)
{
    //Don't even think about drawing until we're on a canvas page
    if (ui->stackWdgt->currentWidget() != ui->canvasPg)// &&
//            ui->stackWdgt->currentWidget() != ui->guestPg)
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
        this->switchScreenToShow(ScreensInWINMain::canvas);
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

VMCanvas WINMain::initCanvasVM()
{
    return VMCanvas([this]() {      //Lambda to refresh the canvas
        this->redrawWhateverCurrentCanvasIsShowing();
    },
    [this](IShape* shapeToEdit) {   //Lambda to edit a shape
        qDebug() << "gonna edit" << shapeToEdit->id;    //TODO
    });
}

void WINMain::redrawWhateverCurrentCanvasIsShowing()
{
    //Put a "delay (even though the delay is 0)" on this so the redraws happen at the right time
    QTimer::singleShot(0, this, [this]()
    {
        this->update();
        if (this->ui->stackWdgt->currentWidget() == this->ui->canvasPg)
        {
            this->ui->canvasVw->update();
        }
        //    else if (this->ui->stackWdgt->currentWidget() == this->ui->guestPg)
        //    {
        //        this->ui->guestCanvasVw->update();
        //    }
    });
}

void WINMain::switchScreenToShow(ScreensInWINMain screen)
{
    switch (screen)
    {
    case guest:
//        ui->stackWdgt->setCurrentWidget(ui->guestPg);
        switchScreenToShow(ScreensInWINMain::welcome);  //TODO replace this line with the comment above
        redrawWhateverCurrentCanvasIsShowing();
        break;
    case canvas:
        ui->stackWdgt->setCurrentWidget(ui->canvasPg);
        redrawWhateverCurrentCanvasIsShowing();
        break;
    case welcome:
        ui->stackWdgt->setCurrentWidget(ui->welcomePg);
        break;
    }
}

void WINMain::initAddRectBt()
{
    connect(ui->addRectBt, &QPushButton::clicked, ui->addRectBt, [this]()
    {
        dlgAddShapeRect = new DLGShapeAdderRect(nullptr,
                                                DLGShapeAdderRect::Mode::RectCreate,
                                                [this](IShape* rectIn)
        {
            this->vm.addShape(rectIn);
        });
        dlgAddShapeRect->setAttribute(Qt::WA_DeleteOnClose);
        dlgAddShapeRect->show();
    });
}

void WINMain::initAddSquareBt()
{
    connect(ui->addSquareBt, &QPushButton::clicked, ui->addSquareBt, [this]()
    {
        dlgAddShapeRect = new DLGShapeAdderRect(nullptr,
                                                DLGShapeAdderRect::Mode::SquareCreate,
                                                [this](IShape* rectIn)
        {
            this->vm.addShape(rectIn);
        });
        dlgAddShapeRect->setAttribute(Qt::WA_DeleteOnClose);
        dlgAddShapeRect->show();
    });
}

void WINMain::initCanvasBackBt()
{
    connect(ui->canvasPgBackBt, &QPushButton::clicked, ui->canvasPgBackBt, [this]()
    {
        vm.persistCanvasToStorage();
        this->switchScreenToShow(ScreensInWINMain::guest);
    });
}

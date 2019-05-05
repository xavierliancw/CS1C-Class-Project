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
    rowNumberFromPickUpEvent = -1;
    ui->canvasPgLayerListVw->viewport()->installEventFilter(this);
    initCanvasBackBt();
    initAddRectBt();
    initAddSquareBt();
    initLayerSelectionBehavior();
    ui->splitter->setSizes(QList<int>() << 1 << 1); //This evens out canvas and editor UI somehow

    //Start the refresh timer that live renders the canvas
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, refreshTimer, [this]()
    {
        this->redrawWhateverCurrentCanvasIsShowing();
    });
    refreshTimer->start(100);

    switchScreenToShow(ScreensInWINMain::welcome);  //Force welcome screen on start
}

WINMain::~WINMain()
{
    refreshTimer->stop();
    delete refreshTimer;
    for (LCShapeLayer* freeThis: layerVwCells)
    {
        delete freeThis;
    }
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
    for (int x = vm.getNumberOfShapesOnCanvas(); x > 0; --x)
    {
        vm.getShapeAtLayer(x - 1)->draw(painter);
    }
    painter.end();
}

bool WINMain::eventFilter(QObject *object, QEvent *event)
{
    //The event is happening in the layers list view
    if (object == ui->canvasPgLayerListVw->viewport())
    {
        QPoint pos;           //Helps model determine which row to drop to
        QModelIndex model;    //Determines row drop location
        QListWidget *listVw;  //The layer list view (just so I can type less

        //On drop events
        if (QDropEvent* castedDropEvent = dynamic_cast<QDropEvent*>(event))
        {
            listVw = ui->canvasPgLayerListVw;
            pos = castedDropEvent->pos();
            model = listVw->indexAt(pos);

            switch (event->type())
            {
            case QEvent::DragEnter:
                rowNumberFromPickUpEvent = listVw->currentRow();
                break;
            case QEvent::Drop:
                //Ignore Qt's default drop behavior
                castedDropEvent->setDropAction(Qt::IgnoreAction);

                //Don't reorder backing data if row number is invalid
                if (rowNumberFromPickUpEvent != -1)
                {
                    //Ask the view model to reorder the data
                    vm.changeShapeLayer(rowNumberFromPickUpEvent, model.row());
                }
                refreshLayersVw();
                rowNumberFromPickUpEvent = -1;  //Reset this
                break;
            default:
                break;
            }
        }
    }
    return false;
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
    return VMCanvas([this]()    //Lambda to refresh the UI elements on the canvas
    {
        this->refreshLayersVw();
    },
    [this](IShape* shapeToEdit) //Lambda to edit a shape
    {
        qDebug() << "gonna edit" << shapeToEdit->id;    //TODO
    });
}

void WINMain::refreshLayersVw()
{
    int shapeCount = static_cast<int>(vm.getNumberOfShapesOnCanvas());
    QListWidget *listVw = ui->canvasPgLayerListVw;

    //Things break if shape count is somehow negative, so ensure that doesn't ever happen
    if (shapeCount < 0) {return;}

    //I am super lazy. Who cares about performance? Tear it all down!
    for (int x = 0; x < layerVwCells.size(); ++x)
    {
        delete layerVwCells[x];
    }
    layerVwCells.clear();
    listVw->clear();

    //Build it back up!
    for (int x = 0; x < shapeCount; ++x)
    {
        QListWidgetItem* newRow = new QListWidgetItem(listVw, 0);
        LCShapeLayer* newCell = new LCShapeLayer();
        listVw->addItem(newRow);
        listVw->setItemWidget(newRow, newCell);
        newRow->setSizeHint(newCell->minimumSizeHint());
        newCell->populateWith(vm.getShapeAtLayer(x),
                              [this](int delID)
        {
            qDebug() << "Delete " << delID;
        },
        [this](int edID)
        {
            qDebug() << "edit " << edID;
        });
        layerVwCells.push_back(newCell);
    }
}

void WINMain::redrawWhateverCurrentCanvasIsShowing()
{
        if (this->ui->stackWdgt->currentWidget() == this->ui->canvasPg)
        {
            this->update();
            this->ui->canvasVw->update();
        }
        //    else if (this->ui->stackWdgt->currentWidget() == this->ui->guestPg)
        //    {
        //        this->update();
        //        this->ui->guestCanvasVw->update();
        //    }
}

void WINMain::switchScreenToShow(ScreensInWINMain screen)
{
    switch (screen)
    {
    case guest:
//        ui->stackWdgt->setCurrentWidget(ui->guestPg);
        switchScreenToShow(ScreensInWINMain::welcome);  //TODO replace this line with the comment above
        break;
    case canvas:
        ui->stackWdgt->setCurrentWidget(ui->canvasPg);
        refreshLayersVw();
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
        dlgAddShapeRect = new DLGShapeGenEditRectangles(nullptr,
                                                DLGShapeGenEditRectangles::Mode::RectCreate,
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
        dlgAddShapeRect = new DLGShapeGenEditRectangles(nullptr,
                                                DLGShapeGenEditRectangles::Mode::SquareCreate,
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

void WINMain::initLayerSelectionBehavior()
{
    connect(ui->canvasPgLayerListVw, &QListWidget::itemSelectionChanged, ui->canvasPgLayerListVw,
            [this]()
    {
        qDebug() << "current selection is: " << ui->canvasPgLayerListVw->currentRow(); //TODO finish thisss
    });
}

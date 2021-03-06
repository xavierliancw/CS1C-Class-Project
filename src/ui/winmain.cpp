#include "winmain.h"
#include "ui_winmain.h"

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain),
    vm(initCanvasVM())
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/final_icon.png"));
    QCoreApplication::setApplicationName("Golden Cone Graphics");
    setWindowTitle("Golden Cone Graphics");

    //Setup start screen's gif by stacking widgets on top of each other
    movie = new QMovie(":/image/car.gif");
    ui->movieLbl->setMovie(movie);
    ui->movieLbl->setAlignment(Qt::AlignCenter);
    QStackedLayout *stackLay = new QStackedLayout;
    stackLay->addWidget(ui->welcomeFrame);
    stackLay->addWidget(ui->movieLbl);
    stackLay->setStackingMode(QStackedLayout::StackAll);
    ui->welcomePg->setLayout(stackLay);
    ui->movieLbl->show();
    QSize movieSize = QApplication::desktop()->size();
    movieSize.setHeight(movieSize.height() - 50);   //Contact us button is 50 tall
    movie->setScaledSize(movieSize);
    movie->start();

    //Initialize UI on welcome page
    initStartBt();
    initContactUsBt();
    initTestimonialCreateBt();
    ui->welcomeTestimonialListVw->viewport()->setAutoFillBackground(false);
    refreshTestimonials();

    //Initialize guest preview page
    initGuestAuthenticateBt();
    initGuestBackBt();

    //Initialze UI on the canvas page
    rowNumberFromPickUpEvent = -1;
    ui->canvasPgLayerListVw->viewport()->installEventFilter(this);
    initCanvasBackBt();
    initRectEditor();
    initLayerSelectionBehavior();
    ui->splitter->setSizes(QList<int>() << 1 << 1); //This evens out canvas and editor UI somehow
    initPropertyInspector();
    initVertexEditor();
    initTxtEditor();
    initReportGenBt();

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
    delete movie;
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
    if (ui->stackWdgt->currentWidget() != ui->canvasPg &&
            ui->stackWdgt->currentWidget() != ui->guestPreviewPg)
    {
        return;
    }
    //Instnantiate a painter that'll draw on the canvas view
    QPainter painter;

    //Figure out which canvas we're drawing on
    if (ui->stackWdgt->currentWidget() == ui->canvasPg)
    {
        painter.begin(ui->canvasVw);
    }
    else if (ui->stackWdgt->currentWidget() == ui->guestPreviewPg)
    {
        painter.begin(ui->guestCanvasVw);
    }
    else
    {
        return;
    }
    //Begin by wiping all drawings
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
        updatePropInspectorVisibility();
    }
    return QMainWindow::eventFilter(object, event);
}

void WINMain::initStartBt()
{
    connect(ui->startBt, &QPushButton::clicked, ui->startBt, [this]()
    {
        this->switchScreenToShow(ScreensInWINMain::guest);
    });
    connect(ui->quitBt, &QPushButton::clicked, ui->quitBt, [this]() {this->close();});
}

void WINMain::initContactUsBt()
{
    QPixmap pixmap(":/image/final_icon.png");
    QIcon ButtonIcon(pixmap);
    ui->contactBt->setIcon(ButtonIcon);
    //ui->contactBt->setIconSize(pixmap.rect().size());
   ui->contactBt->setIconSize(QSize(65, 65));
    connect(ui->contactBt, &QPushButton::clicked, ui->contactBt, [this]()
    {
        contactFormWin = new DLGContactForm(this);
        contactFormWin->setAttribute(Qt::WA_DeleteOnClose);
        contactFormWin->exec();
    });
}

void WINMain::initTestimonialCreateBt()
{
    connect(ui->addTestimonialBt, &QPushButton::clicked, ui->addTestimonialBt, [this]()
    {
        DLGTestimonialCreate *testimonialFormWin = new DLGTestimonialCreate(this, [this]()
        {
            this->refreshTestimonials();
        });
        testimonialFormWin->setAttribute(Qt::WA_DeleteOnClose);
        testimonialFormWin->exec();
    });
}

VMCanvas WINMain::initCanvasVM()
{
    return VMCanvas([this]() {   //Lambda to refresh the UI elements on the canvas
        this->refreshLayersVw();
    },
    [this](IShape* shapeToEdit) { //Lambda to edit a shape
        this->summonDlgThatEdits(shapeToEdit);
    });
}

void WINMain::initGuestBackBt()
{
    connect(ui->guestPreviewBackBt, &QPushButton::clicked, ui->guestPreviewBackBt, [this]()
    {
        this->ui->stackWdgt->setCurrentWidget(ui->welcomePg);
    });
}

void WINMain::initGuestAuthenticateBt()
{
    connect(ui->guestPreviewEditBt, &QPushButton::clicked, ui->guestPreviewEditBt, [this]()
    {
        dlgLogin = new DLGLoginScreen(this, [this]()
        {
            this->switchScreenToShow(ScreensInWINMain::canvas);
        });
        dlgLogin->setAttribute(Qt::WA_DeleteOnClose);
        dlgLogin->exec();
    });
}

void WINMain::initCanvasBackBt()
{
    connect(ui->canvasPgBackBt, &QPushButton::clicked, ui->canvasPgBackBt, [this]()
    {
        this->ui->stackWdgt->setCurrentWidget(ui->welcomePg);
    });
}

void WINMain::summonDlgThatEdits(IShape * shapeToEdit)
{
    switch (shapeToEdit->getShape())
    {
    case IShape::ShapeType::Line:
        if (ShapeLine* castedLine = dynamic_cast<ShapeLine*>(shapeToEdit))
        {
            DLGEditorVertices* vertEditor = new DLGEditorVertices(this, castedLine);
            vertEditor->setAttribute(Qt::WA_DeleteOnClose);
            vertEditor->exec();
        }
        break;
    case IShape::ShapeType::Text:
        if (ShapeText* casted = dynamic_cast<ShapeText*>(shapeToEdit))
        {
            DLGEditorText* txtEditor = new DLGEditorText(this,
                                                         casted,
                                                         [](ShapeText*){});
            txtEditor->setAttribute(Qt::WA_DeleteOnClose);
            txtEditor->exec();
        }
        break;
    case IShape::ShapeType::Circle:
        if (ShapeCircle* casted = dynamic_cast<ShapeCircle*>(shapeToEdit))
        {
            DLGEditorRectFrame* rectEditor = new DLGEditorRectFrame(this,  casted);
            rectEditor->setAttribute(Qt::WA_DeleteOnClose);
            rectEditor->exec();
        }
        break;
    case IShape::ShapeType::Square:
        if (ShapeSquare* casted = dynamic_cast<ShapeSquare*>(shapeToEdit))
        {
            DLGEditorRectFrame* rectEditor = new DLGEditorRectFrame(this, casted);
            rectEditor->setAttribute(Qt::WA_DeleteOnClose);
            rectEditor->exec();
        }
        break;
    case IShape::ShapeType::Ellipse:
        if (ShapeEllipse* casted = dynamic_cast<ShapeEllipse*>(shapeToEdit))
        {
            DLGEditorRectFrame* rectEditor = new DLGEditorRectFrame(this, casted);
            rectEditor->setAttribute(Qt::WA_DeleteOnClose);
            rectEditor->exec();
        }
        break;
    case IShape::ShapeType::NoShape:
        qDebug() << "Tried to edit a NoShape";
        break;
    case IShape::ShapeType::Polygon:
        if (ShapePolygon* castedPoly = dynamic_cast<ShapePolygon*>(shapeToEdit))
        {
            DLGEditorVertices* vertEditor = new DLGEditorVertices(this, castedPoly);
            vertEditor->setAttribute(Qt::WA_DeleteOnClose);
            vertEditor->exec();
        }
        break;
    case IShape::ShapeType::Polyline:
        if (ShapePolyLine* castedPoly = dynamic_cast<ShapePolyLine*>(shapeToEdit))
        {
            DLGEditorVertices* vertEditor = new DLGEditorVertices(this, castedPoly);
            vertEditor->setAttribute(Qt::WA_DeleteOnClose);
            vertEditor->exec();
        }
        break;
    case IShape::ShapeType::Triangle:
        if (ShapeTriangle* casted = dynamic_cast<ShapeTriangle*>(shapeToEdit))
        {
            DLGEditorVertices* vertEditor = new DLGEditorVertices(this, casted);
            vertEditor->setAttribute(Qt::WA_DeleteOnClose);
            vertEditor->exec();
        }
        break;
    case IShape::ShapeType::Rectangle:
        if (ShapeRect* casted = dynamic_cast<ShapeRect*>(shapeToEdit))
        {
            DLGEditorRectFrame* rectEditor = new DLGEditorRectFrame(this, casted);
            rectEditor->setAttribute(Qt::WA_DeleteOnClose);
            rectEditor->exec();
        }
        break;
    }
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
        newCell->populateWith(
                    vm.getShapeAtLayer(x),
                    [this](int delID) { //Lambda to delete a shape
            vm.removeShapeAtLayer(delID);
            this->refreshLayersVw();
        },
        [this](int edID) {vm.editShapeAtLayer(edID);} //Lambda to edit a shape
        );
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
    else if (this->ui->stackWdgt->currentWidget() == this->ui->guestPreviewPg)
    {
        this->update();
        this->ui->guestCanvasVw->update();
    }
}

void WINMain::switchScreenToShow(ScreensInWINMain screen)
{
    switch (screen)
    {
    case guest:
        ui->stackWdgt->setCurrentWidget(ui->guestPreviewPg);
        redrawWhateverCurrentCanvasIsShowing();
        break;
    case canvas:
        ui->stackWdgt->setCurrentWidget(ui->canvasPg);
        refreshLayersVw();
        break;
    case welcome:
        ui->stackWdgt->setCurrentWidget(ui->welcomePg);
        refreshTestimonials();
        break;
    }
}

void WINMain::initLayerSelectionBehavior()
{
    updatePropInspectorVisibility();
    connect(ui->canvasPgLayerListVw,
            &QListWidget::itemSelectionChanged,
            ui->canvasPgLayerListVw,
            [this]()
    {
        this->updatePropInspectorVisibility();

        //Update the property inspector regardless
        this->updatePropertyInspectorFor(
                    vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow())
                    );
    });
}

void WINMain::initPropertyInspector()
{
    //Brush color
    connect(ui->propInspBrushClrBt, &QPushButton::clicked, ui->propInspBrushClrBt, [this]()
    {
        int currentRow = ui->canvasPgLayerListVw->currentRow();
        if (currentRow < 0 || currentRow > vm.getNumberOfShapesOnCanvas() - 1) {return;}
        QColor curColor = vm.getShapeAtLayer(currentRow)->brush.color();
        QColor color = QColorDialog::getColor(curColor, this);
        if (color.isValid())
        {
            IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
            currShape->brush.setColor(color);
            this->updatePropertyInspectorFor(currShape);
        }
    });

    //Brush style
    connect(ui->propInspBrushStyleCB,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->propInspBrushStyleCB,
            [this](int newSelection)
    {
        IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
        switch (newSelection)
        {
        case 0: currShape->brush.setStyle(Qt::BrushStyle::NoBrush); break;
        case 1: currShape->brush.setStyle(Qt::BrushStyle::SolidPattern); break;
        case 2: currShape->brush.setStyle(Qt::BrushStyle::HorPattern); break;
        case 3: currShape->brush.setStyle(Qt::BrushStyle::VerPattern); break;
        case 4: currShape->brush.setStyle(Qt::BrushStyle::CrossPattern); break;
        case 5: currShape->brush.setStyle(Qt::BrushStyle::BDiagPattern); break;
        case 6: currShape->brush.setStyle(Qt::BrushStyle::FDiagPattern); break;
        case 7: currShape->brush.setStyle(Qt::BrushStyle::DiagCrossPattern); break;
        case 8: currShape->brush.setStyle(Qt::BrushStyle::Dense1Pattern); break;
        case 9: currShape->brush.setStyle(Qt::BrushStyle::Dense2Pattern); break;
        case 10: currShape->brush.setStyle(Qt::BrushStyle::Dense3Pattern); break;
        case 11: currShape->brush.setStyle(Qt::BrushStyle::Dense4Pattern); break;
        case 12: currShape->brush.setStyle(Qt::BrushStyle::Dense5Pattern); break;
        case 13: currShape->brush.setStyle(Qt::BrushStyle::Dense6Pattern); break;
        case 14: currShape->brush.setStyle(Qt::BrushStyle::Dense7Pattern); break;
        default: currShape->brush.setStyle(Qt::BrushStyle::NoBrush); break;
        }
    });

    //Pen cap style
    connect(ui->propInspPenCapCB,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->propInspPenCapCB,
            [this](int newSelection)
    {
        IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
        switch (newSelection)
        {
        case 0: currShape->pen.setCapStyle(Qt::PenCapStyle::SquareCap); break;
        case 1: currShape->pen.setCapStyle(Qt::PenCapStyle::RoundCap); break;
        case 2: currShape->pen.setCapStyle(Qt::PenCapStyle::FlatCap); break;
        default: currShape->pen.setCapStyle(Qt::PenCapStyle::SquareCap); break;
        }
    });

    //Pen color
    connect(ui->propInspPenClrBt, &QPushButton::clicked, ui->propInspPenClrBt, [this]()
    {
        QColor curColor = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow())->pen.color();
        QColor color = QColorDialog::getColor(curColor, this);
        if (color.isValid())
        {
            IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
            currShape->pen.setColor(color);
            this->updatePropertyInspectorFor(currShape);
        }
    });

    //Pen join style
    connect(ui->propInspPenJoinStyleCB,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->propInspPenJoinStyleCB,
            [this](int newSelection)
    {
        IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
        switch (newSelection)
        {
        case 0: currShape->pen.setJoinStyle(Qt::PenJoinStyle::BevelJoin); break;
        case 1: currShape->pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin); break;
        case 2: currShape->pen.setJoinStyle(Qt::PenJoinStyle::MiterJoin); break;
        case 3: currShape->pen.setJoinStyle(Qt::PenJoinStyle::SvgMiterJoin); break;
        default: currShape->pen.setJoinStyle(Qt::PenJoinStyle::BevelJoin); break;
        }
    });

    //Pen style
    connect(ui->propInspPenStyleCB,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->propInspPenStyleCB,
            [this](int newSelection)
    {
        IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
        switch (newSelection)
        {
        case 0: currShape->pen.setStyle(Qt::PenStyle::SolidLine); break;
        case 1: currShape->pen.setStyle(Qt::PenStyle::DashLine); break;
        case 2: currShape->pen.setStyle(Qt::PenStyle::DotLine); break;
        case 3: currShape->pen.setStyle(Qt::PenStyle::DashDotLine); break;
        case 4: currShape->pen.setStyle(Qt::PenStyle::DashDotDotLine); break;
        case 5: currShape->pen.setStyle(Qt::PenStyle::NoPen); break;
        default: currShape->pen.setStyle(Qt::PenStyle::SolidLine); break;
        }
    });

    //Pen width
    connect(ui->propInspPenWidthSB,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->propInspPenWidthSB,
            [this](int newVal)
    {
        IShape* currShape = vm.getShapeAtLayer(ui->canvasPgLayerListVw->currentRow());
        currShape->pen.setWidth(newVal);
    });
}

void WINMain::updatePropertyInspectorFor(const IShape * shape)
{
    //Brush color
    ui->propInspBrushClrBt->
            setStyleSheet(QString("background-color: %1").arg(shape->brush.color().name()));

    //Brush style
    int brushStyleIndex = -1;
    switch (shape->brush.style())
    {
    case Qt::BrushStyle::NoBrush: brushStyleIndex = 0; break;
    case Qt::BrushStyle::SolidPattern: brushStyleIndex = 1; break;
    case Qt::BrushStyle::HorPattern: brushStyleIndex = 2; break;
    case Qt::BrushStyle::VerPattern: brushStyleIndex = 3; break;
    case Qt::BrushStyle::CrossPattern: brushStyleIndex = 4; break;
    case Qt::BrushStyle::BDiagPattern: brushStyleIndex = 5; break;
    case Qt::BrushStyle::FDiagPattern: brushStyleIndex = 6; break;
    case Qt::BrushStyle::DiagCrossPattern: brushStyleIndex = 7; break;
    case Qt::BrushStyle::Dense1Pattern: brushStyleIndex = 8; break;
    case Qt::BrushStyle::Dense2Pattern: brushStyleIndex = 9; break;
    case Qt::BrushStyle::Dense3Pattern: brushStyleIndex = 10; break;
    case Qt::BrushStyle::Dense4Pattern: brushStyleIndex = 11; break;
    case Qt::BrushStyle::Dense5Pattern: brushStyleIndex = 12; break;
    case Qt::BrushStyle::Dense6Pattern: brushStyleIndex = 13; break;
    case Qt::BrushStyle::Dense7Pattern: brushStyleIndex = 14; break;
    case Qt::BrushStyle::LinearGradientPattern: brushStyleIndex = -1; break;
    case Qt::BrushStyle::RadialGradientPattern: brushStyleIndex = -1; break;
    case Qt::BrushStyle::ConicalGradientPattern: brushStyleIndex = -1; break;
    case Qt::BrushStyle::TexturePattern: brushStyleIndex = -1; break;
    }
    if (brushStyleIndex != -1) {ui->propInspBrushStyleCB->setCurrentIndex(brushStyleIndex);}

    //Pen cap style
    int capStyleIndex = -1;
    switch (shape->pen.capStyle())
    {
    case Qt::PenCapStyle::SquareCap: capStyleIndex = 0; break;
    case Qt::PenCapStyle::RoundCap: capStyleIndex = 1; break;
    case Qt::PenCapStyle::FlatCap: capStyleIndex = 2; break;
    case Qt::PenCapStyle::MPenCapStyle: capStyleIndex = -1; break;
    }
    if (capStyleIndex != -1) {ui->propInspPenCapCB->setCurrentIndex(capStyleIndex);}

    //Pen color
    ui->propInspPenClrBt->
            setStyleSheet(QString("background-color: %1").arg(shape->pen.color().name()));

    //Pen join style
    int joinStyleIndex = -1;
    switch (shape->pen.joinStyle())
    {
    case Qt::PenJoinStyle::BevelJoin: joinStyleIndex = 0; break;
    case Qt::PenJoinStyle::RoundJoin: joinStyleIndex = 1; break;
    case Qt::PenJoinStyle::MiterJoin: joinStyleIndex = 2; break;
    case Qt::PenJoinStyle::SvgMiterJoin: joinStyleIndex = 3; break;
    case Qt::PenJoinStyle::MPenJoinStyle: joinStyleIndex = -1; break;
    }
    if (joinStyleIndex != -1) {ui->propInspPenJoinStyleCB->setCurrentIndex(joinStyleIndex);}

    //Pen style
    int penStyleIndex = -1;
    switch (shape->pen.style())
    {
    case Qt::PenStyle::SolidLine: penStyleIndex = 0; break;
    case Qt::PenStyle::DashLine: penStyleIndex = 1; break;
    case Qt::PenStyle::DotLine: penStyleIndex = 2; break;
    case Qt::PenStyle::DashDotLine: penStyleIndex = 3; break;
    case Qt::PenStyle::DashDotDotLine: penStyleIndex = 4; break;
    case Qt::PenStyle::NoPen: penStyleIndex = 5; break;
    case Qt::PenStyle::MPenStyle: penStyleIndex = -1; break;
    case Qt::PenStyle::CustomDashLine: penStyleIndex = -1; break;
    }
    if (penStyleIndex != -1) {ui->propInspPenStyleCB->setCurrentIndex(penStyleIndex);}

    //Pen width
    ui->propInspPenWidthSB->setValue(shape->pen.width());
}

void WINMain::initVertexEditor()
{
    connect(ui->addPolygonBt, &QPushButton::clicked, ui->addPolygonBt, [this]()
    {
        DLGEditorVertices *dlgVertexEditor = new DLGEditorVertices(
                    this,
                    IShape::ShapeType::Polygon,
                    [this](IShape* newShapeCallback) {this->vm.addShape(newShapeCallback);}
                );
        dlgVertexEditor->setAttribute(Qt::WA_DeleteOnClose);
        dlgVertexEditor->exec();
    });
    connect(ui->addPolyLineBt, &QPushButton::clicked, ui->addPolyLineBt, [this]()
    {
        DLGEditorVertices *dlgVertexEditor = new DLGEditorVertices(
                    this,
                    IShape::ShapeType::Polyline,
                    [this](IShape* newShapeCallback) {this->vm.addShape(newShapeCallback);}
                );
        dlgVertexEditor->setAttribute(Qt::WA_DeleteOnClose);
        dlgVertexEditor->exec();
    });
    connect(ui->addLineBt, &QPushButton::clicked, ui->addLineBt, [this]()
    {
        DLGEditorVertices *dlgVertexEditor = new DLGEditorVertices(
                    this,
                    IShape::ShapeType::Line,
                    [this](IShape* newShapeCallback) {this->vm.addShape(newShapeCallback);}
                );
        dlgVertexEditor->setAttribute(Qt::WA_DeleteOnClose);
        dlgVertexEditor->exec();
    });
    connect(ui->addTriangleBt, &QPushButton::clicked, ui->addTriangleBt, [this]()
    {
        DLGEditorVertices *dlgVertexEditor = new DLGEditorVertices(
                    this,
                    IShape::ShapeType::Triangle,
                    [this](IShape* newShapeCallback) {this->vm.addShape(newShapeCallback);}
                );
        dlgVertexEditor->setAttribute(Qt::WA_DeleteOnClose);
        dlgVertexEditor->exec();
    });
}

void WINMain::initRectEditor()
{
    connect(ui->addRectBt, &QPushButton::clicked, ui->addRectBt, [this]()
    {
        DLGEditorRectFrame* dlg = new DLGEditorRectFrame(
                    this,
                    IShape::ShapeType::Rectangle,
                    [this](IShape* newShape) {vm.addShape(newShape);}
                );
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->exec();
    });
    connect(ui->addSquareBt, &QPushButton::clicked, ui->addSquareBt, [this]()
    {
        DLGEditorRectFrame* dlg = new DLGEditorRectFrame(
                    this,
                    IShape::ShapeType::Square,
                    [this](IShape* newShape) {
                vm.addShape(newShape);
    }
                );
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->exec();
    });
    connect(ui->addEllipseBt, &QPushButton::clicked, ui->addEllipseBt, [this]()
    {
        DLGEditorRectFrame* dlg = new DLGEditorRectFrame(
                    this,
                    IShape::ShapeType::Ellipse,
                    [this](IShape* newShape) {vm.addShape(newShape);}
                );
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->exec();
    });
    connect(ui->addCircleBt, &QPushButton::clicked, ui->addCircleBt, [this]()
    {
        DLGEditorRectFrame* dlg = new DLGEditorRectFrame(
                    this,
                    IShape::ShapeType::Circle,
                    [this](IShape* newShape) {vm.addShape(newShape);}
                );
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->exec();
    });
}

void WINMain::initTxtEditor()
{
    connect(ui->addTxtBt, &QPushButton::clicked, ui->addTxtBt, [this]()
    {
        DLGEditorText* dlg = new DLGEditorText(this,
                                               nullptr,
                                               [this](ShapeText* newTxt) {vm.addShape(newTxt);});
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->exec();
    });
}

void WINMain::refreshTestimonials()
{
    QJsonArray jsonAr;
    try
    {
        jsonAr = SVCJson::getInstance()->
                readJsonArrayFile(Gimme::theShared()->fileNameForTestimonials);
    }
    catch (SVCJson::JsonFileSystemError fileErr)
    {
        //Do nothing because the file probably doesn't exist yet
    }
    ui->welcomeTestimonialListVw->clear();

    //Regenerate testimonials from the JSON
    for (QJsonValueRef jsonRef: jsonAr)
    {
        DTOTestimonial *test = nullptr;
        if (jsonRef.isObject())
        {
            test = JSONTestimonial::fromJSON(jsonRef.toObject());
        }
        if (test != nullptr)
        {
            ui->welcomeTestimonialListVw->addItem(QString::fromStdString(test->txt) +
                                                  "\n- " +
                                                  QString::fromStdString(test->displayName) +
                                                  "\n\n");
            delete test;
        }
    }
}

void WINMain::updatePropInspectorVisibility()
{
    //Hide or show property inspector when appropriate
    if (ui->canvasPgLayerListVw->currentRow() == -1)
    {
        ui->canvasPgPropInspStck->setCurrentWidget(ui->propInspPg1);
    }
    else
    {
        ui->canvasPgPropInspStck->setCurrentWidget(ui->propInspPg0);
    }
}

void WINMain::initReportGenBt()
{
    connect(ui->reportGenerateBt, &QPushButton::clicked, ui->reportGenerateBt, [this]()
    {
        QVector<IShape*> shapes;
        for (int x = 0; x < vm.getNumberOfShapesOnCanvas(); ++x)
        {
            shapes.push_back(vm.getShapeAtLayer(x));
        }
        DLGShapeReport *dlg = new DLGShapeReport(this, shapes);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->exec();
    });
}

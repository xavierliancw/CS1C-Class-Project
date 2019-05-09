#include "dlgeditorvertices.h"
#include "ui_dlgeditorvertices.h"

DLGEditorVertices::DLGEditorVertices(QWidget *parent,
                                     IShape::ShapeType shapeTypeToGen,
                                     std::function<void(IShape*)>dlgDidGenerateNewShape):
    QDialog(parent),
    ui(new Ui::DLGEditorVertices),
    dlgDidGenerateNewShape(dlgDidGenerateNewShape),
    vm(initVM())
{
    ui->setupUi(this);
    vm.resetStateUsing(shapeTypeToGen);
    initRestOfUI();
}

DLGEditorVertices::DLGEditorVertices(QWidget *parent, IShape *shapeToEdit):
    QDialog(parent),
    ui(new Ui::DLGEditorVertices),
    dlgDidGenerateNewShape([](IShape*){}),
vm(initVM())
{
    ui->setupUi(this);
    vm.resetStateUsing(shapeToEdit);
    initRestOfUI();
}

DLGEditorVertices::~DLGEditorVertices()
{
    delete ui;
}

bool DLGEditorVertices::eventFilter(QObject *object, QEvent *event)
{
    //The event is happening in the list view
    if (object == ui->listVw->viewport())
    {
        QPoint pos;           //Helps model determine which row to drop to
        QModelIndex model;    //Determines row drop location
        QListWidget *listVw;  //The layer list view (just so I can type less

        //On drop events
        if (QDropEvent* castedDropEvent = dynamic_cast<QDropEvent*>(event))
        {
            listVw = ui->listVw;
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
                    vm.reorderVertex(rowNumberFromPickUpEvent, model.row());
                }
                refreshListVw();
                rowNumberFromPickUpEvent = -1;  //Reset this
                break;
            default:
                break;
            }
        }
    }
    return parent()->eventFilter(object, event);
}

void DLGEditorVertices::initRestOfUI()
{
    ui->listVw->viewport()->installEventFilter(this);
    connect(ui->btCancel, &QPushButton::clicked, ui->btCancel, [this]() {this->close();});
    connect(ui->btSubmit, &QPushButton::clicked, ui->btSubmit, [this]()
    {
        vm.finishEditing();
        this->close();
    });
    connect(ui->btAddVertex, &QPushButton::clicked, ui->btAddVertex, [this]()
    {
        vm.createVertex();
    });
}

VMEditorVertices DLGEditorVertices::initVM()
{
    return VMEditorVertices([this](bool hideAddBt)      //Controls add vertex bt visibility
    {ui->btAddVertex->setVisible(!hideAddBt);},
    [this](bool enableSubmitBt)                         //Controls submit bt enable/disable
    {ui->btSubmit->setEnabled(enableSubmitBt);},
    [this]()                                            //Triggers at init or full resets
    {
        ui->lblTitle->setText(vm.getLblTxtTitle());
        ui->btCancel->setText(vm.getBtTxtCancel());
        ui->btSubmit->setText(vm.getBtTxtSubmit());
        this->refreshListVw();
    },
    [this](IShape* newShape)                            //Event when a new shape is generated
    {this->dlgDidGenerateNewShape(newShape);},
    [this](bool deleteBtsDisabled)                      //Controls if delete buttons are enabled
    {this->deleteBtsEnabled = !deleteBtsDisabled;},
[this]()                                                //Controls when vertex list refreshes
{this->refreshListVw();});
}

void DLGEditorVertices::refreshListVw()
{
    int vertexCount = vm.getCurrentVertexCount();
    QListWidget *listVw = ui->listVw;

    //Things break if shape count is somehow negative, so ensure that doesn't ever happen
    if (vertexCount < 0) {return;}

    //I am super lazy. Who cares about performance? Tear it all down!
    for (int x = 0; x < vertexEditCells.size(); ++x)
    {
        delete vertexEditCells[x];
    }
    vertexEditCells.clear();
    listVw->clear();

    //Build it back up!
    for (int x = 0; x < vertexCount; ++x)
    {
        QListWidgetItem* newRow = new QListWidgetItem(listVw, 0);
        LCEditVertex* newCell = new LCEditVertex(this,
                                                 [this](int vertToUpdate, QString x, QString y) {
            //This lambda is called whenever text is changed in the vertex editor cell
            vm.updateVertexAt(vertToUpdate, x, y);
        },
        [this](int vertToDelete) {
            //This lambda is called whenever the vertex editor cell's delete bt has been pressed
            vm.removeVertexAt(vertToDelete);
        });
        listVw->addItem(newRow);
        listVw->setItemWidget(newRow, newCell);
        newRow->setSizeHint(newCell->minimumSizeHint());
        newCell->populateWith(x, std::get<0>(vm.getVertexAt(x)), std::get<1>(vm.getVertexAt(x)),
                              deleteBtsEnabled);
        vertexEditCells.push_back(newCell);
    }
}

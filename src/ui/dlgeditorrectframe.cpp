#include "dlgeditorrectframe.h"
#include "ui_dlgeditorrectframe.h"

DLGEditorRectFrame::DLGEditorRectFrame(QWidget *parent,
                                       IShape::ShapeType shapeTypeToGen,
                                       std::function<void(IShape*)> dlgDidGiveRectResult):
    QDialog(parent),
    ui(new Ui::DLGEditorRectFrame),
    dlgDidGiveRectResult(dlgDidGiveRectResult),
    vm(initVM())
{
    ui->setupUi(this);
    vm.setModeWithDependency(shapeTypeToGen);
}

DLGEditorRectFrame::DLGEditorRectFrame(QWidget *parent,
                                       IShape *shapeToEdit):
    QDialog(parent),
    ui(new Ui::DLGEditorRectFrame),
    dlgDidGiveRectResult([](IShape*){}),
    vm(initVM())
{
    ui->setupUi(this);
    vm.setModeWithDependency(shapeToEdit);
}

DLGEditorRectFrame::~DLGEditorRectFrame()
{
    delete intValidator;
    delete ui;
}

VMEditorRectFrame DLGEditorRectFrame::initVM()
{
    return VMEditorRectFrame(
                [this](bool enableSubmitBt)
    {
        ui->addBt->setEnabled(enableSubmitBt);
    },
    [this](bool fourthPromptIsHidden)
    {
        ui->prompt4Lbl->setVisible(!fourthPromptIsHidden);
        ui->field4LE->setVisible(!fourthPromptIsHidden);
    },
    [this](IShape* newShapeGeneration)
    {
        dlgDidGiveRectResult(newShapeGeneration);
    },
    [this]() {return ui->field1LE->text();},
[this]() {return ui->field2LE->text();},
[this]() {return ui->field3LE->text();},
[this]() {return ui->field4LE->text();},
[this]()
{
QWidget::setWindowTitle(vm.getTxtLblTitle());
ui->titleLbl->setText(vm.getTxtLblTitle());
ui->prompt1Lbl->setText(vm.getTxtPrompt1());
ui->prompt2Lbl->setText(vm.getTxtPrompt2());
ui->prompt3Lbl->setText(vm.getTxtPrompt3());
ui->prompt4Lbl->setText(vm.getTxtPrompt4());
ui->addBt->setText(vm.getTxtBtSubmit());
ui->cancelBt->setText(vm.getTxtBtCancel());

//Set the initial field values (especially if we're editing so user can edit the old values)
ui->field1LE->setText(vm.getRawX());
ui->field2LE->setText(vm.getRawY());
ui->field3LE->setText(vm.getRawW());
ui->field4LE->setText(vm.getRawH());

this->initGeneralUI();
}
);
}

void DLGEditorRectFrame::initGeneralUI()
{
    //Set up add button
    connect(ui->addBt, &QPushButton::clicked, ui->addBt, [this]()
    {
        vm.performActionsWhenDoneEditing();
        this->close();
    });
    //Set up cancel button
    connect(ui->cancelBt, &QPushButton::clicked, ui->cancelBt, [this]()
    {
        this->close();
    });
    //Have each field update state as text is typed
    connect(ui->field1LE, &QLineEdit::textChanged, ui->field1LE, [this]()
    {
        vm.performActionsOnInputEdit();
    });
    connect(ui->field2LE, &QLineEdit::textChanged, ui->field2LE, [this]()
    {
        vm.performActionsOnInputEdit();
    });
    connect(ui->field3LE, &QLineEdit::textChanged, ui->field3LE, [this]()
    {
        vm.performActionsOnInputEdit();
    });
    connect(ui->field4LE, &QLineEdit::textChanged, ui->field4LE, [this]()
    {
        vm.performActionsOnInputEdit();
    });

    //Force fields to only except integers
    intValidator = new QIntValidator();
    ui->field1LE->setValidator(intValidator);
    ui->field2LE->setValidator(intValidator);
    ui->field3LE->setValidator(intValidator);
    ui->field4LE->setValidator(intValidator);
}

#include "dlgtestimonialcreate.h"
#include "ui_dlgtestimonialcreate.h"

DLGTestimonialCreate::DLGTestimonialCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGTestimonialCreate)
{
    ui->setupUi(this);

    //Initialize the view model
    vm = initializedVM();

    //Submit button behavior
    connect(ui->saveBt, &QPushButton::clicked, this, [this]()
    {
        this->vm->submitTestimonial(ui->topTE->text(), ui->bodyTE->toPlainText());
    });
    //Success screen done button behavior
    connect(ui->successFinishBt, &QPushButton::clicked, this, [this]()
    {
        close();
    });

    //Initialize visible stuff
    ui->saveBt->setText(vm->saveBtTxt);
    ui->prompt0Lbl->setText(vm->prompt1Txt);
    ui->prompt1Lbl->setText(vm->prompt2Txt);
    ui->successLbl->setText(vm->successMsg);
    ui->successFinishBt->setText(vm->successDoneBtTxt);
}

DLGTestimonialCreate::~DLGTestimonialCreate()
{
    delete vm;
    vm = nullptr;
    delete ui;
}

VMTestimonialCreate* DLGTestimonialCreate::initializedVM()
{
    VMTestimonialCreate* newVm = new VMTestimonialCreate([this](bool submitBtEnabled)
    {
        //Let VM control the access to the submit button
        ui->saveBt->setEnabled(submitBtEnabled);
    },
    [this](bool showSuccessScreen)
    {
        //Let VM control when the success screen appears
        if (showSuccessScreen)
        {
            ui->stackedWidget->setCurrentWidget(ui->pgSuccess);
        }
        else
        {
            ui->stackedWidget->setCurrentWidget(ui->pgTestimonialForm);
        }
    });
    //Give VM ability to watch the top LE
    connect(ui->topTE, &QLineEdit::textChanged, this, [this]()
    {
        this->vm->updateInputState(ui->topTE->text(), ui->bodyTE->toPlainText());
    });
    //Give VM ability to watch the body TE
    connect(ui->bodyTE, &QPlainTextEdit::textChanged, this, [this]()
    {
        this->vm->updateInputState(ui->topTE->text(), ui->bodyTE->toPlainText());
    });
    return newVm;
}

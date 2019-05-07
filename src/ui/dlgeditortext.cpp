#include "dlgeditortext.h"
#include "ui_dlgeditortext.h"

DLGEditorText::DLGEditorText(QWidget *parent,
                             ShapeText* txtToEdit,
                             std::function<void(ShapeText*)> newGeneratedTxtCallback):
    QDialog(parent),
    ui(new Ui::DLGEditorText),
    existingTxtBeingEdited(txtToEdit),
    newGeneratedTxtCallback(newGeneratedTxtCallback)
{
    ui->setupUi(this);

    ui->btCancel->setText("Cancel");
    if (existingTxtBeingEdited == nullptr)
    {
        //Generate a new shape when done
        ui->btSubmit->setText("Add");
        QWidget::setWindowTitle("New Text");
        ui->lblTitle->setText("New Text");
    }
    else
    {
        //Edit the text that was passed in
        ui->btSubmit->setText("Apply");
        QWidget::setWindowTitle("Text Edit");
        ui->lblTitle->setText("Text Edit");

        ui->leX->setText(QString::number(existingTxtBeingEdited->m_point.x()));
        ui->leY->setText(QString::number(existingTxtBeingEdited->m_point.y()));
        ui->txtEdit->setPlainText(existingTxtBeingEdited->m_text);
    }

    connect(ui->btCancel, &QPushButton::clicked, ui->btCancel, [this]()
    {
        this->close();
    });

    connect(ui->btEditStyle, &QPushButton::clicked, ui->btEditStyle, [this]()
    {
        bool ok;
        fontToApply = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    });

    connect(ui->btSubmit, &QPushButton::clicked, ui->btSubmit, [this]()
    {
        bool validInts = true;
        int x = ui->leX->text().toInt(&validInts);
        int y = ui->leY->text().toInt(&validInts);
        if (!validInts) {return;}   //Prevent edits when invalid

        if (existingTxtBeingEdited == nullptr)
        {
            //Generate a new shape when done
            ShapeText* newTxt = new ShapeText(x, y, ui->txtEdit->toPlainText());
            newTxt->font = fontToApply;
            this-> newGeneratedTxtCallback(newTxt);
        }
        else
        {
            //Edit the text that was passed in
            existingTxtBeingEdited->m_point = QPoint(x, y);
            existingTxtBeingEdited->font = fontToApply;
            existingTxtBeingEdited->m_text = ui->txtEdit->toPlainText();
        }
        this->close();
    });

    intValidator = new QIntValidator();
    ui->leX->setValidator(intValidator);
    ui->leY->setValidator(intValidator);

    connect(ui->leX, &QLineEdit::textChanged, ui->leX, [this]()
    {
        updateSubmitBt();
    });
    connect(ui->leY, &QLineEdit::textChanged, ui->leY, [this]()
    {
        updateSubmitBt();
    });
    updateSubmitBt();
}

DLGEditorText::~DLGEditorText()
{
    delete intValidator;
    delete ui;
}

void DLGEditorText::updateSubmitBt()
{
    bool validInts = true;
    ui->leX->text().toInt(&validInts);
    ui->leY->text().toInt(&validInts);
    ui->btSubmit->setEnabled(validInts);
}

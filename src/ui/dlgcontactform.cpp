#include "dlgcontactform.h"
#include "ui_dlgcontactform.h"

DLGContactForm::DLGContactForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGContactForm)
{
    ui->setupUi(this);
}

DLGContactForm::~DLGContactForm()
{
    delete ui;
}

void DLGContactForm::sendCustomerInquiry()
{
    QString email = ui->emailLE->text();
    QString inquiryTxt = ui->inquiryTE->toPlainText();

    //Don't save if something's empty
    if (email.isEmpty() || inquiryTxt.isEmpty()) {return;}

    //Create the model
    DTOCustomerInquiry inquiry;
    inquiry.custEmail = email.toUtf8().constData();
    inquiry.inquiryTxt = inquiryTxt.toUtf8().constData();
    inquiry.timestamp_unix = static_cast<int>(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                    ).count()
                );

    //Serialize to JSON
    QJsonObject json = JSONCustomerInquiry::toJSON(inquiry);

    //Retrieve inquiries from storage if any
    QJsonArray existingInquiries;
    try
    {
        existingInquiries = SVCJson::getInstance()->readJsonArrayFile(
                    Gimme::theShared()->fileNameForSavedCustomerInquiries
                    );
    }
    catch (SVCJson::JsonFileSystemError fileErr)
    {
        //Don't worry about it because there are no inquiries in storage
    }
    //Add the new testimonial
    existingInquiries.append(json);

    //Save it
    SVCJson::getInstance()->persistJSONToLocalFileSystem(
                existingInquiries, Gimme::theShared()->fileNameForSavedCustomerInquiries
                );
    showSuccessScreen();
}

void DLGContactForm::showSuccessScreen()
{
    throw;
}
